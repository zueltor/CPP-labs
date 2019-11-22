//
// Created by Damir on 09.11.2019.
//

#include "Edge.h"

void Edge::set(const std::pair<int, int> &f, const std::pair<int, int> &s) {
    first_endpoint = f;
    second_endpoint = s;
    if (f == s) {
        direction = UNKNOWN;
    } else {
        setDirection();
    }
}

void Edge::setDirection() {
    if (first_endpoint.first == second_endpoint.first) {
        direction = HORIZONTAL;
    } else if (first_endpoint.second == second_endpoint.second) {
        direction = VERTICAL;
    } else {
        direction = UNKNOWN;
    }
}

void Edge::changeBoundary(const std::pair<int, int> &b) {
    if ((first_endpoint.first > b.first && first_endpoint.second == b.second) ||
        (first_endpoint.first == b.first && first_endpoint.second > b.second)) {
        first_endpoint = b;
    } else {
        second_endpoint = b;
    }
    if (direction == UNKNOWN) {
        setDirection();
    }
}
