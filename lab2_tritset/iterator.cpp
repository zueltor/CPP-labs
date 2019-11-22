//
// Created by Damir on 05.10.2019.
//

#include "iterator.h"

Iterator::Iterator(unsigned *u, size_t cur_ind) : a(u), cur_ind(cur_ind) {}

Iterator Iterator::operator++() {
    cur_ind++;
    return *this;
}

Iterator Iterator::operator++(int junk) {
    Iterator tmp(this->a, this->cur_ind);
    cur_ind++;
    return tmp;
}

bool Iterator::operator==(const Iterator &it) const {
    return (this->cur_ind == it.cur_ind && this->a == it.a);
}

bool Iterator::operator!=(const Iterator &it) const {
    return !(*this == it);
}

Trit Iterator::operator*() {
    unsigned n = cur_ind / 4 / sizeof(unsigned);
    unsigned mask = 0b11 << (2 * (cur_ind % (4 * sizeof(unsigned))));
    unsigned bits = mask & a[n];
    bits = bits >> (2 * (cur_ind % (4 * sizeof(unsigned))));
    return bits_to_trit(bits);
}
