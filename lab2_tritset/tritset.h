#include "trit.h"
#include "iterator.h"
#include <iostream>
#include <unordered_map>


#ifndef TRITSET_H
#define TRITSET_H

class Tproxy;

class Tritset {
public:
    explicit Tritset(size_t _size = 0);

    Tritset(const Tritset &ts);

    Tritset(std::initializer_list<Trit> il);

    size_t capacity() const;

    ~Tritset();

    Tproxy operator[](size_t i);

    Trit operator[](size_t i) const;

    Tritset &operator=(const Tritset &ts);

    Tritset operator|=(const Tritset &ts);

    Tritset operator|(const Tritset &ts) const;

    Tritset &operator&=(const Tritset &ts);

    Tritset operator&(const Tritset &ts) const;

    Tritset operator~() const;

    Tritset &operator+=(const Tritset &ts);

    Tritset operator+(const Tritset &ts) const;

    bool operator==(const Tritset &ts) const;

    bool operator!=(const Tritset &ts) const;

    Trit get(size_t i) const;

    size_t length() const;

    size_t cardinality(const Trit &value) const;

    std::unordered_map<Trit, size_t> cardinality() const;

    void shrink();

    void trim(size_t length);

    void print(std::ostream &output) const;

    Iterator begin() const;

    Iterator end() const;

private:

    unsigned operator_helper(unsigned uint1, unsigned uint2, char op) const;

    void resize(size_t length);

    void swap(Tritset &t);

    void recount_length();

private:
    friend class Tproxy;

    friend class Iterator;

    size_t size;
    unsigned *set;
    size_t cur_ind;
    size_t logical_length;
};


class Tproxy {
public:
    Tproxy(Tritset &ts, size_t i);

    Tproxy &operator=(const Trit &trit);

    Tproxy &operator=(const Tproxy &tp);

    bool operator==(const Tproxy &tp) const;

    bool operator==(const Trit &t) const;

private:
    size_t i;
    Tritset *ts;
};

std::ostream &operator<<(std::ostream &os, const Trit &t);

size_t uintsize(unsigned i);

#endif //TRITSET_H
