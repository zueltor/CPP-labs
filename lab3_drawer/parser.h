//
// Created by Damir on 19.10.2019.
//

#include "shape.h"
#include "canvas.h"

#ifndef DRAWER_PARSER_H
#define DRAWER_PARSER_H

int contains(std::string s, char c);

void Parser(Canvas &shapes, std::istream &in);

static void check_params(std::vector<std::string> &params);

#endif //DRAWER_PARSER_H
