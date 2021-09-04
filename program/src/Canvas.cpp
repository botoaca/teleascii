#include "include/Canvas.h"

Canvas::Canvas(int _h, int _w, std::string _path)
{
    h = _h;
    w = _w;
    path = _path;
    
    canvas.resize(w);
    for (int i = 0; i < w; i++)
    {
        canvas[i].resize(h);
        for (int j = 0; j < h; j++)
        {
            canvas[i][j].resize(3);
        }
    }

    std::ifstream input(path);
    std::cout << "Parsing data...\n";
    __j = json::parse(input);
    input.close();
    CLEAR_SCREEN();
    std::cout << "Parsing data... Done" << std::endl;
}

void
Canvas::Draw()
{
    std::ostringstream buf;
    for (unsigned i = 0; i < canvas.size(); i++)
    {
        for (unsigned j = 0; j < canvas.at(i).size(); j++)
        {
            int rgb[3] = {
                canvas.at(i).at(j).at(0),
                canvas.at(i).at(j).at(1),
                canvas.at(i).at(j).at(2)
            };
            std::string to_print = "\033[48;2;"
                + std::to_string(rgb[0])
                + ";" + std::to_string(rgb[1])
                + ";" + std::to_string(rgb[2])
                + "m "
                + "\033[0;00m";
            buf << to_print;
        }
        buf << '\n';
    }
    std::cout << "\033[0;0H" << buf.str();
}

void
Canvas::PlayFrame(int idx, std::chrono::milliseconds ft)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (unsigned i = 0; i < canvas.size(); i++)
    {
        for (unsigned j = 0; j < canvas.at(i).size(); j++)
        {
            for (unsigned k = 0; k < canvas.at(i).at(j).size(); k++)
            {
                canvas.at(i).at(j).at(k) = __j.at(std::to_string(idx)).at(j).at(i).at(k).get<int>();
            }
        }
    }

    Draw();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::this_thread::sleep_for(std::chrono::milliseconds(ft - elapsed));
}

void
Canvas::PlayAnimation(std::chrono::milliseconds ft)
{
    unsigned idx = 0;
    for (; idx < __j.size(); idx++) {
        PlayFrame(idx, ft);
    }
}