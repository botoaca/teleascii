from PIL import Image
import cv2

import argparse
import json
import os
import shutil

black    = (128, 128, 128)
red      = (255, 0, 0)
green    = (0, 255, 0)
yellow   = (255, 255, 0)
blue     = (0, 0, 255)
magenta  = (255, 0, 255)
cyan     = (0, 255, 255)
white    = (255, 255, 255)

colors = [
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
]

tresh = 7

def luminance(pixel):
    R = pixel[0]
    G = pixel[1]
    B = pixel[2]
    return (0.299 * R + 0.587 * G + 0.114 * B)

def is_similar(pixel_a, pixel_b, threshold):
    return abs(luminance(pixel_a) - luminance(pixel_b)) < threshold

def set_frame(frame_number, img, data, mode = 1):
    iy = []
    for y in range(img.size[1]):
        ix = []
        for x in range(img.size[0]):
            pix = img.getpixel((x, y))
            if mode == 1:
                verdict = (0, 0, 255)
                for c in colors:
                    if is_similar(pix, c, tresh):
                        verdict = c
                        break
                ix.append(colors.index(verdict))
            else:
                if pix < (128, 128, 128):
                    ix.append(0)
                else:
                    ix.append(7)
        iy.append(ix)
    data[str(frame_number)] = iy

def main():
    mode = 1
    frame_count = 0
    data = {}

    argparser = argparse.ArgumentParser()
    argparser.add_argument("-i", "--input", required=True, help="Input video file", type=str)
    argparser.add_argument("-m", "--mode", required=True, help="Color mode", default=1, type=int)
    args = argparser.parse_args()
    
    mode = args.mode
    video = cv2.VideoCapture(args.input)
    success, frame = video.read()
    
    init()

    while success:
        path = f"frames/frame_{frame_count}.png"

        cv2.imwrite(path, frame)
        img = Image.open(path)
        img.save(path)

        set_frame(frame_count, img, data, mode)

        success, frame = video.read()
        print(f"FRAME {frame_count} STATUS: {success}")
        frame_count += 1

    write(f"out/data.json", data)

def init():
    if os.path.exists("frames"):
        shutil.rmtree("frames")
    os.mkdir("frames")
    if not os.path.exists("out"):
        os.mkdir("out")

def write(path, data):
    with open(path, "w") as f:
        json.dump(data, f)

if __name__ == "__main__":
    main()
