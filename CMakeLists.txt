cmake_minimum_required(VERSION 3.8)
project(perceptron++)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

add_executable(perceptron++ src/main.cpp src/mnist/reader.cpp src/mnist/reader.hpp src/nn/NeuralNetwork.cpp src/nn/NeuralNetwork.hpp
        src/perceptron/Neuron.cpp src/perceptron/Neuron.hpp src/perceptron/PerceptronMonoLayer.cpp src/perceptron/PerceptronMonoLayer.hpp src/perceptron/ItemNN.hpp src/perceptron/act_funs.hpp)
target_link_libraries(perceptron++ ${OpenCV_LIBS})
target_link_libraries(perceptron++ ${Boost_LIBS})
