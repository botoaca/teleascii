#include <tuple>

#include "include/Canvas.h"

std::chrono::milliseconds
parse_frametime(const std::string frametime)
{
    size_t pos = frametime.find("ms");
    return std::chrono::milliseconds(std::stoi(frametime.substr(0, pos)));
}

std::tuple<int, int>
parse_res(const std::string res)
{
    std::tuple<int, int> parsed_res;
    size_t pos = res.find('x');
    std::get<0>(parsed_res) = std::stoi(res.substr(0, pos));
    std::get<1>(parsed_res) = std::stoi(res.substr(pos + 1));
    return parsed_res;
}

int
main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: " << argv[0] << " <path_to_input_file> <resolution> <frametime_ms>\n";
        std::cout << "Example: " << argv[0] << " data.json 64x32 40ms" << std::endl;
        return 1;
    }

    std::tuple<int, int> parsed_res = parse_res(argv[2]);
    std::chrono::milliseconds parsed_frametime = parse_frametime(argv[3]);

    CLEAR_SCREEN();
    Canvas(std::get<0>(parsed_res), std::get<1>(parsed_res), argv[1])
        .PlayAnimation(parsed_frametime); // 40ms per frame = 25fps
    
    return 0;
}