#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>
using namespace std::chrono_literals;

#include "Util.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Canvas
{
private:
    int h, w;
    std::string path;
    json __j;

    std::vector<std::vector<std::vector<int>>> canvas;
public:
    Canvas(int, int, std::string);

    void
    Draw();

    void
    PlayFrame(int, std::chrono::milliseconds);

    void
    PlayAnimation(std::chrono::milliseconds);
};

#endif // CANVAS_H