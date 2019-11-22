cmake_minimum_required (VERSION 3.1.0)
project (battleship)

set(CMAKE_CXX_STANDARD 14)
add_executable(battleship main.cpp Field.cpp KeyPoints.cpp Edge.cpp utility.cpp)
add_executable(unittest test.cpp Field.cpp KeyPoints.cpp Edge.cpp utility.cpp)
