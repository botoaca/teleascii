import cv2

import argparse
import json
import os
import shutil

def set_frame(frame_number, img, data, mode = 1):
    width, height = img.shape[:2]
    iy = []
    for y in range(height):
        ix = []
        for x in range(width):
            (b, g, r) = img[x, y]
            if mode == 1:
                ix.append((int(r), int(g), int(b)))
            else:
                if (r, g, b) < (128, 128, 128):
                    ix.append((0, 0, 0))
                else:
                    ix.append((255, 255, 255))
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
        img = cv2.imread(path, cv2.IMREAD_UNCHANGED)
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
