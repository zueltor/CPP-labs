//
// Created by Damir on 09.11.2019.
//

#ifndef BATTLESHIP_KEYPOINTS_H
#define BATTLESHIP_KEYPOINTS_H

#include <list>
#include <vector>
#include <random>
#include "Constants.h"

class KeyPoints {
public:
    KeyPoints();

    void inverse(int n);

    void reevaluate(int n, const std::vector<std::vector<int>> &field);

    std::pair<int, int> choose();

private:
    static const std::vector<std::vector<std::vector<int>>> squares_4x4;
    static const std::vector<std::vector<std::vector<int>>> squares_3x3;
    std::list<std::pair<int, int>> points1;
    std::list<std::pair<int, int>> points2;
    std::list<std::pair<int, int>> points3;

};


#endif //BATTLESHIP_KEYPOINTS_H
