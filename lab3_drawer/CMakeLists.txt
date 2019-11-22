cmake_minimum_required (VERSION 3.1.0)
project (Drawer)

set(CMAKE_CXX_STANDARD 14)
add_executable(drawer main.cpp shape.cpp parser.cpp canvas.cpp utility.cpp)
add_executable(unittest test.cpp shape.cpp parser.cpp canvas.cpp utility.cpp)
