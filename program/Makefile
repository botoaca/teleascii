CXX = g++ --std=c++20
CXXFLAGS = -Wall

all: build build/output

build:
	mkdir build

build/output: build/main.o build/canvas.o build/util.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/canvas.o: src/Canvas.cpp src/include/Canvas.h src/include/nlohmann/json.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/util.o: src/Util.cpp src/include/Util.h
	$(CXX) $(CXXFLAGS) -c $< -o $@