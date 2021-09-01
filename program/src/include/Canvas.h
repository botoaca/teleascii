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

#define BLACK    "\u001b[30m#\u001b[0m"
#define RED      "\u001b[31m#\u001b[0m"
#define GREEN    "\u001b[32m#\u001b[0m"
#define YELLOW   "\u001b[33m#\u001b[0m"
#define BLUE     "\u001b[34m#\u001b[0m"
#define MAGENTA  "\u001b[35m#\u001b[0m"
#define CYAN     "\u001b[36m#\u001b[0m"
#define WHITE    "\u001b[37m#\u001b[0m"

class Canvas
{
private:
    int h, w;
    std::string path;
    json __j;

    std::vector<std::vector<int>> canvas;
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