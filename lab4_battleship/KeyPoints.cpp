//
// Created by Damir on 09.11.2019.
//

#include <iostream>
#include "KeyPoints.h"

const std::vector<std::vector<std::vector<int>>> KeyPoints::squares_4x4 = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}},
                                                                           {{0, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}},
                                                                           {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}},
                                                                           {{0, 0, 0, 1}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}},
                                                                           {{1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}},
                                                                           {{0, 1, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {1, 0, 0, 0}},
                                                                           {{0, 1, 0, 0}, {0, 0, 0, 1}, {1, 0, 0, 0}, {0, 0, 1, 0}},
                                                                           {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}}};

const std::vector<std::vector<std::vector<int>>> KeyPoints::squares_3x3 = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},
                                                                           {{0, 1, 0}, {1, 0, 0}, {0, 0, 1}}};

KeyPoints::KeyPoints() {

    int i, j, k, l;

    std::vector<std::vector<int>> square_4x4 = squares_4x4[1];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (square_4x4[i][j] == 1) {
                for (k = i; k < 10; k += 4) {
                    for (l = j; l < 10; l += 4) {
                        points1.emplace_back(k, l);
                    }
                }
            }
        }
    }

    std::vector<std::vector<int>> square_3x3 = squares_3x3[1];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (square_3x3[i][j] == 1) {
                for (k = i; k < 10; k += 3) {
                    for (l = j; l < 10; l += 3) {
                        points2.emplace_back(k, l);
                    }
                }
            }
        }
    }

    points1.sort([](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
        return rand() % 2;
    });
    points2.sort([](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
        return rand() % 2;
    });


    if (rand() % 2) {
        inverse(1);
    }
    if (rand() % 2) {
        inverse(2);
    }

}

void KeyPoints::inverse(int n) {
    if (n == 1) {
        for (auto &p:points1) {
            p = {p.first, 9 - p.second};
        }
    } else {
        for (auto &p:points2) {
            p = {p.first, 9 - p.second};
        }
    }
}

void KeyPoints::reevaluate(int n, const std::vector<std::vector<int>> &field) {
    if (n == 4) {
        points1.clear();
    } else if (n == 3) {
        points2.clear();
        points3.clear();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (field[i][j] == UNKNOWN) {
                    points3.emplace_back(i, j);
                }
            }
        }
        points3.sort([](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
            return rand() % 2;
        });
    }
}

std::pair<int, int> KeyPoints::choose() {
    for (const auto p:points1) {
        points1.remove(p);
        return p;
    }
    for (const auto p:points2) {
        points2.remove(p);
        return p;
    }
    for (const auto p:points3) {
        points3.remove(p);
        return p;
    }
    return NONE;
}
