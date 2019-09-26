#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <sstream>
#include <utility>
#include "Phrases.h"
#include "Args.h"


bool operator==(const Args &l, const Args &r) {
    return (l.n == r.n && l.filename == r.filename && l.m == r.m);
}

bool operator==(const Pair &l, const Pair &r) {
    return (l.get_freq() == r.get_freq() && l.get_phrase() == r.get_phrase());
}

int do_main(std::istream &in, std::ostream &out, int n, int m) {

    if (n < 1)
        return 0;

    Phrases phrases(n, m);
    unsigned int count_words;
    count_words = phrases.read_words(in);

    if (count_words < n)
        return 0;

    phrases.build();
    phrases.print(out);

    return 0;
}

TEST_CASE("Args test") {
    char *argv[6];
    for (auto &i : argv) {
        i = new char[10];
    }
    strcpy(argv[1], "-m");
    strcpy(argv[2], "3");
    strcpy(argv[3], "-n");
    strcpy(argv[4], "5");
    strcpy(argv[5], "in.txt");
    int n, m;
    std::string filename;
    arg_parse(6, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(5, 3, "in.txt"));
    arg_parse(5, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(5, 3, "-"));
    arg_parse(3, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(2, 3, "-"));
    strcpy(argv[1], "name.txt");
    strcpy(argv[2], "-n");
    strcpy(argv[3], "6");
    strcpy(argv[4], "-m");
    strcpy(argv[5], "9");
    arg_parse(6, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(6, 9, "name.txt"));
    arg_parse(4, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(6, 2, "name.txt"));
    arg_parse(2, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(2, 2, "name.txt"));
    arg_parse(1, argv, n, m, filename);
    REQUIRE (Args(n, m, filename) == Args(2, 2, "-"));
    for (auto &i : argv) {
        delete[] i;
    }
}

TEST_CASE("Functions test") {
    std::stringstream in;
    std::stringstream out;
    in.clear();
    Phrases p;
    p.read_words(in);
    p.build();
    p.print(out);
    REQUIRE(p.word.empty());
    REQUIRE(p.pair.empty());
    REQUIRE(out.str().empty());
    in.clear();
    in << "a a a a";
    p.n = 1000;
    p.read_words(in);
    p.build();
    p.print(out);
    std::vector<std::string> word = {"a", "a", "a", "a"};
    REQUIRE(p.word == word);
    REQUIRE(p.pair.empty());
    REQUIRE(out.str().empty());
    p.n = 2;
    p.m = 1000;
    p.print(out);
    REQUIRE(out.str().empty());
    p.m = 2;
    in.clear();
    in << "a b c d e f g a a a b b";
    p.read_words(in);
    word = {"a", "b", "c", "d", "e", "f", "g", "a", "a", "a", "b", "b"};
    REQUIRE(p.word == word);
    in.clear();
    in << "a a a a a a f";
    word = {"a", "a", "a", "a", "a", "a", "f"};
    p.read_words(in);
    REQUIRE(p.word == word);
    in.clear();
    in << "a a a a";
    word = {"a", "a", "a", "a"};
    std::vector<Pair> pair = {Pair(3, "a a")};
    p.read_words(in);
    p.build();
    p.print(out);
    REQUIRE(p.word == word);
    REQUIRE(pair == p.pair);
    REQUIRE(out.str() == "a a (3)\n");
    out.str("");
    p.m = 1000;
    p.print(out);
    REQUIRE(out.str().empty());
    p.m = 2;
    p.n = 3;
    p.build();
    p.print(out);
    pair = {Pair(2, "a a a")};
    REQUIRE(pair == p.pair);
    REQUIRE(out.str() == "a a a (2)\n");
    in.clear();
    out.str("");
    in << "a a a b b a b c c b a";
    p.n = 1;
    p.m = 3;
    pair = {Pair(5, "a"), Pair(4, "b"), Pair(2, "c")};
    p.read_words(in);
    p.build();
    p.print(out);
    REQUIRE(pair == p.pair);
    REQUIRE(out.str() == "a (5)\nb (4)\n");
    p.m = 5;
    out.str("");
    p.print(out);
    REQUIRE(out.str() == "a (5)\n");
    p.m = 6;
    out.str("");
    p.print(out);
    REQUIRE(out.str().empty());
    in.clear();
    in << "a b a b a b c d c d c d e f";
    p.n = 2;
    p.m = 3;
    word = {"a", "b", "a", "b", "a", "b", "c", "d", "c", "d", "c", "d", "e", "f"};
    p.read_words(in);
    p.build();
    p.print(out);
    REQUIRE(p.word == word);
    REQUIRE(out.str() == "a b (3)\nc d (3)\n");
    p.m = 2;
    out.str("");
    p.print(out);
    std::string f = out.str();
    REQUIRE(out.str() == "a b (3)\nc d (3)\nb a (2)\nd c (2)\n");
}

TEST_CASE("Result test") {
    std::stringstream in;
    std::stringstream out;
    int i;
    for (i = 0; i < 2; i++) {
        in << "a b c a" << std::endl;
        in << "b c d" << std::endl;
    }
    do_main(in, out, 3, 4);
    REQUIRE(out.str() == "a b c (4)\n");
    out.str("");
    in.clear();
    for (i = 0; i < 100; i++) {
        in << "a a a ";
    }
    do_main(in, out, 3, 3);
    std::string f = out.str();
    REQUIRE(out.str() == "a a a (298)\n");
}

