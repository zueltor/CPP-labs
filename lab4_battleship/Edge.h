//
// Created by Damir on 09.11.2019.
//

#ifndef BATTLESHIP_EDGE_H
#define BATTLESHIP_EDGE_H

#include <utility>
#include "Constants.h"

class Edge {
public:
    Edge() = default;

    void set(const std::pair<int, int> &f, const std::pair<int, int> &s);

    void setDirection();

    void changeBoundary(const std::pair<int, int> &b);


    int direction{};
    std::pair<int, int> first_endpoint;
    std::pair<int, int> second_endpoint;

};


#endif //BATTLESHIP_EDGE_H
