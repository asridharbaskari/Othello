cmake_minimum_required(VERSION 3.25)
project(Othello)

set(CMAKE_CXX_STANDARD 17)

add_executable(Othello src/main.cpp src/Controller/Controller.cpp src/Controller/Controller.h src/View/StandardView.cpp src/View/StandardView.h src/Model/Player.cpp src/Model/Player.h src/Model/Model.cpp src/Model/Model.h src/Model/Utility.h src/View/View.cpp src/View/View.h)
