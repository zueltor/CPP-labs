cmake_minimum_required (VERSION 3.1.0)
project (Phrases)

set(CMAKE_CXX_STANDARD 14)
add_executable(phrases main.cpp Phrases.cpp Args.cpp)
add_executable(unittest test.cpp Phrases.cpp Args.cpp)
