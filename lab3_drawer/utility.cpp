//
// Created by Damir on 19.10.2019.
//

#include <sstream>
#include <unistd.h>
#include "utility.h"
#include "canvas.h"
#include "parser.h"


Segment::Segment(std::pair<int, int> p1, std::pair<int, int> p2) : start(std::move(p1)), end(std::move(p2)) {}

std::pair<int, int> operator+(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

std::pair<int, int> operator-(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
    return {p1.first - p2.first, p1.second - p2.second};
}

int do_main(int argc, char **argv, bool fill) {
    Canvas shapes;
    int opt = 0;
    optind = 1;
    std::string filename, out;
    int err = 0;
    while ((opt = getopt(argc, argv, "o:")) != -1) {
        switch (opt) {
            case 'o':
                out = optarg;
                break;
            case '?':
            default :
                err = 1;
                break;
        }
    }
    filename = argv[optind];
    try {
        if (err == 1) {
            throw std::runtime_error("Invalid option\n");
        }

        if (!filename.empty()) {
            std::fstream in(filename);
            if (!in.is_open()) {
                throw std::runtime_error("File could not be opened\n");
            }
            Parser(shapes, in);
        } else {
            Parser(shapes, std::cin);
        }
    }
    catch (const std::exception &ex) {
        std::cout << ex.what();
        return 0;
    }
    if (!out.empty()) {
        if (out.length() < 5 || out.compare(out.length() - 4, 4, ".bmp") != 0) {
            out += ".bmp";
        }
        shapes.draw(out, fill);
    } else {
        shapes.draw("", fill);
    }
    return 0;
}

std::string to_string(int n) {
    std::stringstream out;
    out << n;
    return out.str();
}

void to_lower(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}
