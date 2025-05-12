CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I/usr/include/opencv4
OPENCV = `pkg-config --cflags --libs opencv4`

compile:
	@$(CXX) $(CXXFLAGS) -o ./build/asclii main.cpp $(OPENCV)
