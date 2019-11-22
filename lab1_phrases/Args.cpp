#include "Args.h"
#include "cstring"
void arg_parse(int argc, char *argv[], int &n, int &m, std::string &filename) {
    bool nflag = false,
            mflag = false,
            nameflag = false;
    n = 2;
    m = 2;
    filename = "-";
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-n") && i + 1 != argc && !nflag) {
            n = strtol(argv[i + 1], nullptr, 10);
            nflag = true;
            i++;
        } else if (!strcmp(argv[i], "-m") && i + 1 != argc && !mflag) {
            m = strtol(argv[i + 1], nullptr, 10);
            mflag = true;
            i++;
        } else if (!nameflag) {
            filename = argv[i];
            nameflag = true;
        } else {
            return;
        }
    }

}