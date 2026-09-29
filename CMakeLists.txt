cmake_minimum_required(VERSION 3.20)

project(Flip7_NN)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Flip7_NN
    files/Flip7.cpp
    files/Players.cpp
    files/Game.cpp
    files/neural_network.cpp
)