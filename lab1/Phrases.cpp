#include "Phrases.h"
#include <algorithm>

unsigned int Phrases::read_words(std::istream &input) {
    std::string w;
    word.clear();
    unsigned int count = 0;
    while (input >> w) {
        count++;
        word.push_back(w);
    }
    return count;
}

void Phrases::build() {
    unsigned int j,
            i;
    if (word.size() < n)
        return;
    unsigned int size = word.size() - n;
    std::string key = word[0];
    std::map<std::string, int> phrase;

    for (i = 1; i < n; i++) {
        key += " " + word[i];
    }
    phrase[key]++;
    for (i = 0; i < size; i++) {
        key.erase(0, word[i].length() + 1);
        if (key.empty())
            key += word[i + n];
        else key += " " + word[i + n];
        phrase[key]++;
    }
    pair.clear();
    for (const auto &x:phrase) {
        pair.emplace_back(x.second, x.first);
    }

    std::sort(pair.begin(), pair.end(), [](Pair const &a, Pair const &b) {
        return a.get_freq() > b.get_freq();
    });;
}

void Phrases::print(std::ostream &out) const {
    for (auto const &x:pair) {
        if (x.get_freq() >= m)
            out << x.get_phrase() << " (" << x.get_freq() << ")" << std::endl;
    }
}