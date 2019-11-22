//
// Created by Damir on 27.09.2019.
//

#ifndef TRIT_H
#define TRIT_H

enum class Trit {
    F, U, T
};

Trit operator&(const Trit &a, const Trit &b);

Trit &operator&=(Trit &a, const Trit &b);

Trit operator|(const Trit &a, const Trit &b);

Trit &operator|=(Trit &a, const Trit &b);

Trit operator~(const Trit &a);

unsigned trit_to_int(const Trit &t);

Trit bits_to_trit(unsigned bits);

#endif //TRIT_H
