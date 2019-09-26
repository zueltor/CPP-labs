#include <fstream>
#include "Phrases.h"
#include "Args.h"

int main(int argc, char *argv[]) {
    int n = 2,
            m = 2;
    std::string filename = "-";

    arg_parse(argc,argv,n,m,filename);

    if (n < 1)
        return 0;

    Phrases phrases(n, m);
    unsigned int count_words;
    if (filename == "-") {
        count_words = phrases.read_words(std::cin);
    } else {
        std::ifstream input(filename);
        count_words = phrases.read_words(input);
        input.close();
    }

    if (count_words < n)
        return 0;

    phrases.build();
    phrases.print(std::cout);

    return 0;
}