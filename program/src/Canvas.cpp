#include "include/Canvas.h"

Canvas::Canvas(int _h, int _w, std::string _path)
{
    h = _h;
    w = _w;
    path = _path;
    canvas.resize(w, std::vector<int>(h));

    std::ifstream input(path);
    std::cout << "Parsing data..." << std::endl;
    __j = json::parse(input);
    input.close();
}

void
Canvas::Draw()
{
    std::ostringstream buf;
    for (unsigned i = 0; i < canvas.size(); i++)
    {
        for (unsigned j = 0; j < canvas.at(i).size(); j++)
        {
            switch (canvas.at(i).at(j))
            {
                case 0:     buf << BLACK;           break;
                case 1:     buf << RED;             break;
                case 2:     buf << GREEN;           break;
                case 3:     buf << YELLOW;          break;
                case 4:     buf << BLUE;            break;
                case 5:     buf << MAGENTA;         break;
                case 6:     buf << CYAN;            break;
                case 7:     buf << WHITE;           break;
                default:    buf << BLACK;           break;
            }
        }
        buf << '\n';
    }
    std::cout << buf.str();
}

void
Canvas::PlayFrame(int idx, std::chrono::milliseconds ft)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (unsigned i = 0; i < canvas.size(); i++)
    {
        for (unsigned j = 0; j < canvas.at(i).size(); j++)
        {
            canvas.at(i).at(j) = __j[std::to_string(idx)][i][j].get<int>();
        }
    }
    Draw();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::this_thread::sleep_for(std::chrono::milliseconds(ft - elapsed));
    CLEAR_SCREEN();
}

void
Canvas::PlayAnimation(std::chrono::milliseconds ft)
{
    unsigned idx = 0;
    for (; idx < __j.size(); idx++) {
        PlayFrame(idx, ft);
    }
}