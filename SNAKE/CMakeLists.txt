cmake_minimum_required(VERSION 3.16)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app main.cpp src/Map.cpp src/Food.cpp src/Snake.cpp src/Game.cpp)
