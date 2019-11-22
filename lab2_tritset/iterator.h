//
// Created by Damir on 05.10.2019.
//

#ifndef TRITSET_ITERATOR_H
#define TRITSET_ITERATOR_H

#include <cstddef>
#include "trit.h"

class Iterator {
public:
    Iterator(unsigned *u, size_t cur_ind);

    Iterator operator++();

    Iterator operator++(int junk);

    bool operator==(const Iterator &it) const;

    bool operator!=(const Iterator &it) const;

    Trit operator*();

private:
    size_t cur_ind;
    unsigned *a;
};


#endif //TRITSET_ITERATOR_H
