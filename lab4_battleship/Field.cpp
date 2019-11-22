//
// Created by Damir on 09.11.2019.
//

#include "Field.h"

EnemyField::EnemyField() : prev_hit(NONE), prev_kill(NONE), edge(Edge()), field(10, std::vector<int>(10, 0)) {
}

std::pair<int, int> EnemyField::react(const std::string &action) {
    if (action == "Shoot!") {
        choosePoint();
        return prev_shoot;
    }
    if (action == "Miss") {
        field[prev_shoot.first][prev_shoot.second] = MISS;
        return NONE;
    } else if (action == "Hit") {
        field[prev_shoot.first][prev_shoot.second] = HIT;
        if (prev_hit == NONE) {                 //first hit
            prev_hit = prev_shoot;
            edge.set(prev_hit, prev_hit);
            prev_shoot = chooseDirection();
            return prev_shoot;
        } else {                                //not first hit
            edge.changeBoundary(prev_shoot);
            prev_shoot = chooseNextPoint();
            return prev_shoot;
        }
    } else if (action == "Kill") {
        field[prev_shoot.first][prev_shoot.second] = HIT;
        if (prev_hit == NONE) {                 //1x1 ship
            edge.set(prev_shoot, prev_shoot);
        } else {                                //not 1x1 ship
            prev_hit = NONE;
            edge.changeBoundary(prev_shoot);
        }
        whichShipIsKilled();
        markNeighbours();
        choosePoint();
        return prev_shoot;
    }
    return NONE;
}

void EnemyField::whichShipIsKilled() {
    int dist = (edge.second_endpoint.first - edge.first_endpoint.first == 0) ?
               edge.second_endpoint.second - edge.first_endpoint.second + 1 :
               edge.second_endpoint.first - edge.first_endpoint.first + 1;
    //bool rip = false;
    if (dist == 4) {
        ship4--;
        //rip = true;
        keypoints.reevaluate(4, field);

    } else if (dist == 3) {
        ship3--;
        //rip = true;
    } else if (dist == 2) {
        ship2--;
        //rip = true;
    } else if (dist == 1) {
        ship1--;
    }
    if (ship3 == 0 && ship4 == 0) {          //rip && ship2 <= 0 &&
        keypoints.reevaluate(3, field);
        ship3--;
    }
}

std::pair<int, int> EnemyField::chooseNextPoint() {
    if (edge.direction == HORIZONTAL) {
        if (edge.first_endpoint.second > 0 &&
            field[edge.first_endpoint.first][edge.first_endpoint.second - 1] == UNKNOWN) {
            return {edge.first_endpoint.first, edge.first_endpoint.second - 1};
        } else return {edge.second_endpoint.first, edge.second_endpoint.second + 1};
    } else if (edge.direction == VERTICAL) {
        if (edge.first_endpoint.first > 0 &&
            field[edge.first_endpoint.first - 1][edge.first_endpoint.second] == UNKNOWN) {
            return {edge.first_endpoint.first - 1, edge.first_endpoint.second};
        } else return {edge.second_endpoint.first + 1, edge.second_endpoint.second};
    }
    return NONE;
}

std::pair<int, int> EnemyField::chooseDirection() {
    int imin, imax, jmin, jmax, i, j;
    if (edge.direction == HORIZONTAL) {
        i = edge.first_endpoint.first;
        if (edge.first_endpoint.second > 0) {
            jmin = edge.first_endpoint.second - 1;
        } else {
            jmin = edge.first_endpoint.second;
        }
        if (edge.second_endpoint.second < 9) {
            jmax = edge.second_endpoint.second + 1;
        } else {
            jmax = edge.second_endpoint.second;
        }
        if (field[i][jmin] == UNKNOWN) {
            return {i, jmin};
        } else {
            return {i, jmax};
        }
    } else if (edge.direction == VERTICAL) {
        j = edge.first_endpoint.second;
        if (edge.first_endpoint.first > 0) {
            imin = edge.first_endpoint.first - 1;
        } else {
            imin = edge.first_endpoint.first;
        }
        if (edge.second_endpoint.first < 9) {
            imax = edge.second_endpoint.first + 1;
        } else {
            imax = edge.second_endpoint.first;
        }
        if (field[imin][j] == UNKNOWN) {
            return {imin, j};
        } else {
            return {imax, j};
        }
    } else {

        i = edge.first_endpoint.first,
                j = edge.first_endpoint.second;
        imin = i;
        imax = i;
        jmin = j;
        jmax = j;
        if (i > 0) {
            imin = i - 1;
        }
        if (i < 9) {
            imax = i + 1;
        }
        if (j > 0) {
            jmin = j - 1;
        }
        if (j < 9) {
            jmax = j + 1;
        }
        if (field[imin][j] == UNKNOWN) {
            return {imin, j};
        } else if (field[imax][j] == UNKNOWN) {
            return {imax, j};
        } else if (field[i][jmin] == UNKNOWN) {
            return {i, jmin};
        } else if (field[i][jmax] == UNKNOWN) {
            return {i, jmax};
        }
    }
    return NONE;
}

void EnemyField::markNeighbours() {
    int imin = 0, imax = 0, jmin = 0, jmax = 0;
    if (edge.direction == HORIZONTAL) {
        if (edge.first_endpoint.second > 0) {
            jmin = edge.first_endpoint.second - 1;
        } else {
            jmin = edge.first_endpoint.second;
        }
        if (edge.second_endpoint.second < 9) {
            jmax = edge.second_endpoint.second + 1;
        } else {
            jmax = edge.second_endpoint.second;
        }
        if (edge.first_endpoint.first > 0) {
            imin = edge.first_endpoint.first - 1;
        } else {
            imin = edge.first_endpoint.first;
        }
        if (edge.first_endpoint.first < 9) {
            imax = edge.first_endpoint.first + 1;
        } else {
            imax = edge.first_endpoint.first;
        }
    } else {
        if (edge.first_endpoint.first > 0) {
            imin = edge.first_endpoint.first - 1;
        } else {
            imin = edge.first_endpoint.first;
        }
        if (edge.second_endpoint.first < 9) {
            imax = edge.second_endpoint.first + 1;
        } else {
            imax = edge.second_endpoint.first;
        }
        if (edge.first_endpoint.second > 0) {
            jmin = edge.first_endpoint.second - 1;
        } else {
            jmin = edge.first_endpoint.second;
        }
        if (edge.first_endpoint.first < 9) {
            jmax = edge.first_endpoint.second + 1;
        } else {
            jmax = edge.first_endpoint.second;
        }
    }
    for (int i = imin; i <= imax; i++) {
        for (int j = jmin; j <= jmax; j++) {
            field[i][j] = VISITED;
        }
    }
}

std::pair<int, int> EnemyField::choosePoint() {
    std::pair<int, int> point = NONE;
    if (prev_hit == NONE) {
        do {
            point = keypoints.choose();
            if (point == NONE) {
                break;
            }
        } while (field[point.first][point.second] != 0);
        if (point != NONE && field[point.first][point.second] == 0) {
            prev_shoot = point;
            return prev_shoot;
        }
        throw std::runtime_error("F");
    } else {
        prev_shoot = chooseDirection();
        return prev_shoot;
    }
}

void MyField::arrange() {
    int choice = rand() % 3 + 1;
    std::vector<std::pair<int, int>> forbidden;
    switch (choice) {
        case 1:
            arrangeShipsVariation1(forbidden);
            break;
        case 2:
            arrangeShipsVariation2(forbidden);
            break;
        case 3:
            arrangeShipsVariation3(forbidden);
            break;
        default:
            arrangeShipsVariation1(forbidden);
            break;
    }

    if (rand() % 2) {       //insane field randomizer
        transpose();
    }
    if (rand() % 2) {
        mirror1();
    }
    if (rand() % 2) {
        mirror2();
    }
}

MyField::MyField() : field(10, std::vector<int>(10, 0)) {}

void MyField::print(std::ostream &out) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            out << field[i][j];
        }
        out << std::endl;
    }
}

void MyField::transpose() {
    int i, j, tmp;
    for (i = 0; i < 10; i++) {
        for (j = i + 1; j < 10; j++) {
            tmp = field[i][j];
            field[i][j] = field[j][i];
            field[j][i] = tmp;
        }
    }
}

void MyField::mirror1() {
    int i, j, tmp;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 5; j++) {
            tmp = field[i][j];
            field[i][j] = field[i][10 - j - 1];
            field[i][10 - j - 1] = tmp;
        }
    }
}

void MyField::mirror2() {
    int i, j, tmp;
    for (j = 0; j < 10; j++) {
        for (i = 0; i < 5; i++) {
            tmp = field[i][j];
            field[i][j] = field[i][10 - j - 1];
            field[i][10 - j - 1] = tmp;
        }
    }
}

void MyField::arrangeShipsVariation1(std::vector<std::pair<int, int>> &forbidden) {
    int i, j, k = 0;
    for (j = 0; j < 10; j++) {
        for (i = 0; i < 3; i += 2) {
            field[i][j] = 1;
        }
    }
    field[0][4] = field[0][7] = field[2][3] = field[2][6] = 0;
    while (k < 4) {
        i = rand() % 6 + 4;
        j = rand() % 10;
        if (contains(forbidden, {i, j})) {
            continue;
        } else {
            field[i][j] = 1;
            markPoints(forbidden, {i, j});
            k++;
        }
    }
}

void MyField::arrangeShipsVariation2(std::vector<std::pair<int, int>> &forbidden) {
    int i, j, k = 0;
    for (j = 0; j < 10; j++) {
        for (i = 0; i < 10; i += 9) {
            field[i][j] = 1;
        }
    }
    field[0][4] = field[0][7] = field[9][3] = field[9][6] = 0;
    while (k < 4) {
        i = rand() % 6 + 2;
        j = rand() % 10;
        if (contains(forbidden, {i, j})) {
            continue;
        } else {
            field[i][j] = 1;
            markPoints(forbidden, {i, j});
            k++;
        }
    }
}

void MyField::arrangeShipsVariation3(std::vector<std::pair<int, int>> &forbidden) {
    int i, j, k = 0;
    for (j = 0; j < 10; j++) {
        field[j][0] = field[0][j] = 1;
    }
    field[0][4] = field[0][8] = field[1][0] = field[5][0] = field[8][0] = 0;
    field[1][9] = field[9][1] = 1;
    forbidden.emplace_back(2, 8);
    forbidden.emplace_back(2, 9);
    forbidden.emplace_back(8, 2);
    forbidden.emplace_back(9, 2);
    while (k < 4) {
        i = rand() % 7 + 2;
        j = rand() % 7 + 2;
        if (contains(forbidden, {i, j})) {
            continue;
        } else {
            field[i][j] = 1;
            markPoints(forbidden, {i, j});
            k++;
        }
    }
}
