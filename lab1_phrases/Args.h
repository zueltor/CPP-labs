#include <iostream>
#ifndef HELLOWORLD_ARGS_H
#define HELLOWORLD_ARGS_H


class Args {
public:
    Args(int n, int m, std::string filename) : n(n), m(m), filename(std::move(filename)) {}

    int n;
    int m;
    std::string filename;
};

void arg_parse(int argc, char *argv[], int &n, int &m, std::string &filename);

#endif //HELLOWORLD_ARGS_H
