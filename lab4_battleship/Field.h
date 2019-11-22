//
// Created by Damir on 09.11.2019.
//

#ifndef BATTLESHIP_FIELD_H
#define BATTLESHIP_FIELD_H


#include <iostream>
#include "Constants.h"
#include "Edge.h"
#include "utility.h"
#include "KeyPoints.h"


class MyField {
public:
    MyField();

    void arrange();

    void print(std::ostream &out) const;

private:
    void arrangeShipsVariation1(std::vector<std::pair<int, int>> &forbidden);

    void arrangeShipsVariation2(std::vector<std::pair<int, int>> &forbidden);

    void arrangeShipsVariation3(std::vector<std::pair<int, int>> &forbidden);

    void transpose();

    void mirror1();

    void mirror2();

private:
    std::vector<std::vector<int>> field;
};

class EnemyField {
public:
    EnemyField();

    std::pair<int, int> react(const std::string &action);

private:
    void whichShipIsKilled();

    std::pair<int, int> choosePoint();

    std::pair<int, int> chooseNextPoint();

    std::pair<int, int> chooseDirection();

    void markNeighbours();

private:
    std::pair<int, int> prev_shoot;
    std::pair<int, int> prev_hit;
    std::pair<int, int> prev_kill;
    Edge edge;
    KeyPoints keypoints;
    int ship4{1};
    int ship3{2};
    int ship2{3};
    int ship1{4};
    std::vector<std::vector<int>> field;

};


#endif //BATTLESHIP_FIELD_H
