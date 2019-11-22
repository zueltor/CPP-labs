//
// Created by Damir on 18.10.2019.
//

#include "shape.h"

std::map<std::string, int> Named::shape_count;

std::string Named::generateName(const std::string &name) {
    return name + "." + to_string(++shape_count[name]);
}

Named::Named(std::string name) : name(std::move(name)) {
    if (!this->name.empty()) {
        setName(this->name);
    }
}

void Named::setName(const std::string &_name) {
    name = generateName(_name);
}

std::string Named::getName() const {
    return name;
}

Colored::Colored(int r, int g, int b) : r(r), g(g), b(b) {}

void Colored::setColor(int _r, int _g, int _b) {
    r = _r;
    g = _g;
    b = _b;
}

int Colored::getColor(int parameter) const {
    if (parameter == 1)
        return r;
    else if (parameter == 2)
        return g;
    else return b;
}

std::pair<int, int> Shape::getCenter() const {
    return center;
}

void Shape::setCenter(int x, int y) {
    center = {x, y};
}

Rectangle::Rectangle(int w, int h) : h(h), w(w) {
    setName("Rectangle");
}

Rectangle::Rectangle(const std::vector<std::string> &params) {
    w = std::atoi(params[2].c_str());
    h = std::atoi(params[3].c_str());
    setCenter(std::atoi(params[4].c_str()), std::atoi(params[5].c_str()));
    setColor(std::atoi(params[6].c_str()), std::atoi(params[7].c_str()),
             std::atoi(params[8].c_str()));
}

double Rectangle::square() const {
    return h * w;
}

std::vector<Segment> Rectangle::getSegments() const {
    std::vector<Segment> segments;
    if (h <= 0 || w <= 0)
        return segments;
    std::pair<int, int> center = getCenter();
    std::pair<int, int> hh{0, h / 2};
    std::pair<int, int> ww{w / 2,
                           0};
    std::pair<int, int> v1{center - hh - ww};
    std::pair<int, int> v2{center - hh + ww};
    std::pair<int, int> v3{center + hh - ww};
    std::pair<int, int> v4{center + hh + ww};
    if (w % 2 == 0) {                       //if size is even, shift center by 1 pixel
        v2 = {v2.first - 1, v2.second};
        v4 = {v4.first - 1, v4.second};
    }
    if (h % 2 == 0) {
        v3 = {v3.first, v3.second - 1};
        v4 = {v4.first, v4.second - 1};
    }
    segments = {{v1, v2},
                {v1, v3},
                {v2, v4},
                {v3, v4}};
    return segments;
}

std::vector<Segment> Rectangle::getInnerSegments() const {
    std::vector<Segment> segments;
    if (h <= 0 || w <= 0)
        return segments;
    std::pair<int, int> center = getCenter();
    std::pair<int, int> hh{0, h / 2};
    std::pair<int, int> ww{w / 2, 0};
    std::pair<int, int> v1{center - hh - ww};
    std::pair<int, int> v2{center - hh + ww};
    std::pair<int, int> v3{center + hh - ww};
    if (w % 2 == 0) {                       //if size is even, shift center by 1 pixel
        v2 = {v2.first - 1, v2.second};
    }
    if (h % 2 == 0) {
        v3 = {v3.first, v3.second - 1};
    }
    std::pair<int, int> incr{0, 1};
    v3 = v3 + incr;
    while (v1 != v3) {
        segments.emplace_back(v1, v2);
        v1 = v1 + incr;
        v2 = v2 + incr;
    }
    return segments;
}


std::vector<int> Rectangle::getParameters() const {
    return std::vector<int>{w, h};
}

void Rectangle::setParameters(std::vector<int> params) {
    if (params.size() >= 2) {
        w = params[0];
        h = params[1];
    }
}

Triangle::Triangle(int dx1, int dy1, int dx2, int dy2) : dx1(dx1), dy1(dy1), dx2(dx2), dy2(dy2) {
    setName("Triangle");
}

Triangle::Triangle(int x, int y, int dx1, int dy1, int dx2, int dy2) : dx1(dx1 - x), dy1(dy1 - y), dx2(dx2 - x),
                                                                       dy2(dy2 - y) {
    setCenter(x, y);
    setName("Triangle");
}

Triangle::Triangle(const std::vector<std::string> &params) {
    dx1 = std::atoi(params[2].c_str());
    dy1 = std::atoi(params[3].c_str());
    dx2 = std::atoi(params[4].c_str());
    dy2 = std::atoi(params[5].c_str());
    setCenter(std::atoi(params[6].c_str()), std::atoi(params[7].c_str()));
    setColor(std::atoi(params[8].c_str()), std::atoi(params[9].c_str()),
             std::atoi(params[10].c_str()));
}

double Triangle::square() const {
    double l1 = sqrt(dx1 * dx1 + dy1 * dy1);
    double l2 = sqrt(dx2 * dx2 + dy2 * dy2);
    double l3 = sqrt((dx1 - dx2) * (dx1 - dx2) + (dy1 - dy2) * (dy1 - dy2));
    double p = (l1 + l2 + l3) / 2.0;
    return sqrt(p * (p - l1) * (p - l2) * (p - l3));
}

std::vector<Segment> Triangle::getSegments() const {
    std::pair<int, int> l1{dx1, dy1};
    std::pair<int, int> l2{dx2, dy2};
    std::pair<int, int> center = getCenter();
    std::vector<Segment> segments{{center,      center + l1},
                                  {center,      center + l2},
                                  {center + l1, center + l2}};
    return segments;
}

std::vector<Segment> Triangle::getInnerSegments() const {
    std::pair<int, int> v1 = getCenter();
    std::pair<int, int> v2 = {dx1, dy1};
    std::pair<int, int> v3 = {dx2, dy2};
    std::pair<int, int> dy{0, 1};
    std::pair<int, int> dx;
    std::pair<int, int> incr{0, 1};
    std::vector<Segment> segments;
    v2 = v1 + v2;
    v3 = v1 + v3;
    if (v1.second > v2.second) {
        std::swap(v1, v2);
    }
    if (v2.second > v3.second) {
        std::swap(v2, v3);
    }
    if (v1.second > v2.second) {
        std::swap(v1, v2);
    }                                   //v1 lower than v2 lower than v3 for for definiteness
    std::pair<int, int> n1 = v3 - v1;
    std::pair<int, int> n2 = v2 - v1;
    std::pair<int, int> w = v1, u = v1;
    while (w.second < v2.second) {
        dx = {dy.second * n2.first / n2.second, 0};
        w = v1 + dx + dy;
        dx = {dy.second * n1.first / n1.second, 0};
        u = v1 + dx + dy;
        dy = dy + incr;
        segments.emplace_back(w, u);
    }
    n1 = v3 - u;
    n2 = v3 - v2;
    dy = {0, 1};
    v1 = u;
    while (w.second < v3.second) {
        dx = {dy.second * n2.first / n2.second, 0};
        w = v2 + dx + dy;
        dx = {dy.second * n1.first / n1.second, 0};
        u = v1 + dx + dy;
        dy = dy + incr;
        segments.emplace_back(w, u);
    }
    return segments;
}

std::vector<int> Triangle::getParameters() const {
    return std::vector<int>{dx1, dy1, dx2, dy2};
}

void Triangle::setParameters(std::vector<int> params) {
    if (params.size() >= 4) {
        dx1 = params[0];
        dx2 = params[1];
        dy1 = params[2];
        dy2 = params[3];
    }
}

Circle::Circle(int r) : r(r) {
    setName("Circle");
}

Circle::Circle(const std::vector<std::string> &params) {
    r = std::atoi(params[2].c_str());
    setCenter(std::atoi(params[3].c_str()), std::atoi(params[4].c_str()));
    setColor(std::atoi(params[5].c_str()), std::atoi(params[6].c_str()),
             std::atoi(params[7].c_str()));
}

double Circle::square() const {
    return M_PI * r * r;
}

std::vector<Segment> Circle::getSegments() const {
    std::vector<Segment> segments;
    if (r <= 0) {
        return segments;
    }
    std::pair<int, int> center = getCenter();
    std::pair<int, int> prev = {center.first - r, center.second};
    std::pair<int, int> cur;
    int n = center.first + r;
    for (int i = center.first - r + 1; i <= n; i++) {
        cur = {i, sqrt(r * r - (i - center.first) * (i - center.first)) + center.second};
        segments.emplace_back(prev, cur);
        prev = cur;
    }
    prev = {center.first - r, center.second};
    for (int i = center.first - r + 1; i <= n; i++) {
        cur = {i, -sqrt(r * r - (i - center.first) * (i - center.first)) + center.second};
        segments.emplace_back(prev, cur);
        prev = cur;
    }
    return segments;
}

std::vector<Segment> Circle::getInnerSegments() const {
    std::vector<Segment> segments;
    if (r <= 0) {
        return segments;
    }
    std::pair<int, int> center = getCenter();
    std::pair<int, int> d = {2 * center.first, center.second};
    int x1, x2,
            y = center.second;
    for (int i = 0; i < 2 * r; i++) {
        x1 = (int) (center.first + sqrt(r * r - (y - center.second) * (y - center.second)));
        x2 = d.first - x1;
        segments.push_back({{x1, y},
                            {x2, y}});
        y -= 2 * i;
        x1 = (int) (center.first + sqrt(r * r - (y - center.second) * (y - center.second)));
        x2 = d.first - x1;
        segments.push_back({{x1, y},
                            {x2, y}});
        y += 2 * i + 1;
    }
    return segments;
}

std::vector<int> Circle::getParameters() const {
    return std::vector<int>{r};
}

void Circle::setParameters(std::vector<int> params) {
    if (!params.empty()) {
        r = params[0];
    }
}
