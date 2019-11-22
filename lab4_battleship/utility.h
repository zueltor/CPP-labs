//
// Created by Damir on 09.11.2019.
//

#ifndef BATTLESHIP_UTILITY_H
#define BATTLESHIP_UTILITY_H


#include <utility>
#include <vector>
#include <algorithm>
#include "Field.h"

void battle(std::istream &in, std::ostream &out);

unsigned char convert(int i);

bool contains(const std::vector<std::pair<int, int>> &forbidden, const std::pair<int, int> &p);

void markPoints(std::vector<std::pair<int, int>> &forbidden, const std::pair<int, int> &p);


#endif //BATTLESHIP_UTILITY_H
