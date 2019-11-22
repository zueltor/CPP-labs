//
// Created by Damir on 19.10.2019.
//
#include <exception>
#include "parser.h"
#include "utility.h"

int contains(std::string s, char c) {
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            continue;
        else if (s[i] == c) {
            return ++i;
        } else throw std::runtime_error("Wrong canvas size format");
    }
    throw std::runtime_error("Wrong canvas size format");
}

void Parser(Canvas &shapes, std::istream &in) {
    std::string s;
    int n, m;
    getline(in, s);
    n = std::atoi(s.c_str());
    m = std::atoi(s.c_str() + contains(s, 'x'));
    if (n < 0 || m < 0) {
        throw std::runtime_error("Wrong canvas size format");
    }
    shapes.setCanvasSize(n, m);
    std::vector<std::regex> regex;
    regex.emplace_back(R"(^(Circle)\((\d+)\)\[(-?\d+),(-?\d+)\]\{(?:(\d+),(\d+),(\d+)|(\w+))\}$)",
                       std::regex_constants::icase);
    regex.emplace_back(R"(^(Rectangle)\((\d+),(\d+)\)\[(-?\d+),(-?\d+)\]\{(?:(\d+),(\d+),(\d+)|(\w+))\}$)",
                       std::regex_constants::icase);
    regex.emplace_back(
            R"(^(Triangle)\((-?\d+),(-?\d+),(-?\d+),(-?\d+)\)\[(-?\d+),(-?\d+)]\{(?:(\d+),(\d+),(\d+)|(\w+))\}$)",
            std::regex_constants::icase);
    std::regex rm_spaces(R"(\s+)");
    std::cmatch match;
    std::vector<std::string> params;
    bool found = false;
    while (getline(in, s)) {
        s = std::regex_replace(s, rm_spaces, "");
        for (const auto &regex_form:regex) {
            std::regex_match(s.c_str(), match, regex_form);
            if (!match.empty()) {
                found = true;
                params.clear();
                for (size_t i = 0; i < match.size(); i++) {
                    params.push_back(match.str(i));
                }
                check_params(params);
                shapes.addShape(params);
                break;
            }
        }
        if (found) {
            found = false;
        } else {
            throw std::runtime_error("Wrong input data");
        }
    }
}

void check_params(std::vector<std::string> &params) {
    static std::map<std::string, Colored> color_map = {
            {"red",     Colored(255, 0, 0)},
            {"lime",    Colored(0, 255, 0)},
            {"blue",    Colored(0, 0, 255)},
            {"black",   Colored(0, 0, 0)},
            {"white",   Colored(255, 255, 255)},
            {"cyan",    Colored(0, 255, 255)},
            {"magenta", Colored(255, 0, 255)},
            {"yellow",  Colored(255, 255, 0)},
            {"silver",  Colored(192, 192, 192)},
            {"gray",    Colored(128, 128, 128)},
            {"maroon",  Colored(128, 0, 0)},
            {"olive",   Colored(128, 128, 0)},
            {"green",   Colored(0, 128, 0)},
            {"purple",  Colored(128, 0, 128)},
            {"teal",    Colored(0, 128, 128)},
            {"navy",    Colored(0, 0, 128)},
            {"brown",   Colored(165, 42, 42)}
    };
    size_t n = params.size();
    int n1 = std::atoi(params[n - 2].c_str());
    int n2 = std::atoi(params[n - 3].c_str());
    int n3 = std::atoi(params[n - 4].c_str());
    if (n1 > 255 || n1 < 0 || n2 > 255 || n2 < 0 || n3 > 255 || n3 < 0) {
        throw std::out_of_range("Colors are not in range [0..255]");
    }
    if (!params[n - 1].empty()) {
        std::string color = params[n - 1];
        to_lower(color);
        if (color_map.find(color) == color_map.end()) {
            throw std::runtime_error("Wrong color format");
        }
        params[n - 2] = to_string(color_map[color].getColor(3));
        params[n - 3] = to_string(color_map[color].getColor(2));
        params[n - 4] = to_string(color_map[color].getColor(1));
    }
}