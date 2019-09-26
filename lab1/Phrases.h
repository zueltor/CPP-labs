#include <iostream>
#include <utility>
#include <vector>
#include <map>

#ifndef PHRASES_PHRASES_H
#define PHRASES_PHRASES_H

class Pair {
public:
    Pair(int freq, std::string phrase) : freq(freq), phrase(std::move(phrase)) {}

    int get_freq() const {
        return freq;
    }

    std::string get_phrase() const {
        return phrase;
    }

private:
    int freq;
    std::string phrase;
};


class Phrases {
public:
    explicit Phrases(int n = 2, int m = 2) : n(n), m(m) {}

    unsigned int read_words(std::istream &input);

    void build();

    void print(std::ostream &out) const;

//private:
    std::vector<std::string> word;
    int n;
    int m;
    std::vector<Pair> pair;
};


#endif //PHRASES_PHRASES_H
