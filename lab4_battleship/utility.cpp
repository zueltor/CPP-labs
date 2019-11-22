//
// Created by Damir on 09.11.2019.
//

#include <ctime>
#include "utility.h"
#include <fstream>

unsigned char convert(int i) {
    return i + 'A';
}

bool contains(const std::vector<std::pair<int, int>> &forbidden, const std::pair<int, int> &p) {
    return std::find(forbidden.begin(), forbidden.end(), p) != forbidden.end();
}

void markPoints(std::vector<std::pair<int, int>> &forbidden, const std::pair<int, int> &p) {
    for (int i = p.first - 1; i <= p.first + 1; i++) {
        for (int j = p.second - 1; j <= p.second + 1; j++) {
            forbidden.emplace_back(i, j);
        }
    }
}

void battle(std::istream &in, std::ostream &out) {
    srand(time(nullptr));
    std::string str;
    MyField myfield;
    EnemyField enemyfield;
    std::pair<int, int> shot;
    while (true) {
        getline(in, str);
        if (str == "Arrange!") {
            myfield.arrange();
            myfield.print(out);
        } else if (str == "Shoot!" || str == "Hit" || str == "Kill") {
            shot = enemyfield.react(str);
            out << convert(shot.second) << " " << shot.first << "\n";
        } else if (str == "Miss") {
            enemyfield.react(str);
        } else if (str == "Win!" || str == "Lose") {
            return;
        }
    }

}
