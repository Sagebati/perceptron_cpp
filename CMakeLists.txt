cmake_minimum_required(VERSION 3.9)
project(perceptron)

set(CMAKE_CXX_STANDARD 11)
find_package( OpenCV REQUIRED )
add_executable(perceptron main.cpp util/util.cpp util/util.h reader.cpp reader.hpp NeuralNetwork.cpp NeuralNetwork.hpp)
target_link_libraries( perceptron ${OpenCV_LIBS} )