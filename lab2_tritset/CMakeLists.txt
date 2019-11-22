cmake_minimum_required (VERSION 3.1.0)
project (Tritset)

set(CMAKE_CXX_STANDARD 14)
add_executable(tritset main.cpp trit.cpp iterator.cpp tritset_operators.cpp tritset_methods.cpp)
add_executable(unittest trit.cpp test.cpp iterator.cpp tritset_operators.cpp tritset_methods.cpp)
