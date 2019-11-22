//
// Created by Damir on 19.10.2019.
//
#include <iostream>
#include <algorithm>
#include <regex>

#ifndef DRAWER_UTILITY_H
#define DRAWER_UTILITY_H


class Segment {
public:
    Segment(std::pair<int, int> p1, std::pair<int, int> p2);

private:
    friend class Shape;

    friend class Canvas;

    std::pair<int, int> start;
    std::pair<int, int> end;
};

void to_lower(std::string &str);

std::string to_string(int n);

std::pair<int, int> operator+(const std::pair<int, int> &p1, const std::pair<int, int> &p2);

std::pair<int, int> operator-(const std::pair<int, int> &p1, const std::pair<int, int> &p2);

int do_main(int argc, char **argv, bool fill);

template<typename Shape>
void printNames(const Shape &shape) {
    std::cout << shape.getName();
}

template<typename Shape, typename ...Others>
void printNames(const Shape &shape, const Others &...rest) {
    std::cout << shape.getName() + " ";
    printNames(rest...);
}

template<typename Shape>
void printOutNames(std::ostream &out, const Shape &shape) {
    out << shape.getName();
}

template<typename Shape, typename ...Others>
void printOutNames(std::ostream &out, const Shape &shape, const Others &...rest) {
    out << shape.getName() + " ";
    printOutNames(out, rest...);
}

template<typename T>
double totalArea(const T &shape) {
    return shape.square();
}

template<typename Shape, typename ...Others>
double totalArea(const Shape &shape, const Others &...rest) {
    return shape.square() + totalArea(rest...);
}

#endif //DRAWER_UTILITY_H
