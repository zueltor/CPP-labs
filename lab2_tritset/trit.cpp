#include "trit.h"

Trit operator&(const Trit &a, const Trit &b) {
    if (a == Trit::F || b == Trit::F)
        return Trit::F;
    else if (a == Trit::U || b == Trit::U)
        return Trit::U;
    else return Trit::T;
}

Trit &operator&=(Trit &a, const Trit &b) {
    a = a & b;
    return a;
}

Trit operator|(const Trit &a, const Trit &b) {
    if (a == Trit::T || b == Trit::T)
        return Trit::T;
    else if (a == Trit::U || b == Trit::U)
        return Trit::U;
    else return Trit::F;
}

Trit &operator|=(Trit &a, const Trit &b) {
    a = a | b;
    return a;
}

Trit operator~(const Trit &a) {
    if (a == Trit::F)
        return Trit::T;
    else if (a == Trit::T)
        return Trit::F;
    else return Trit::U;
}

Trit bits_to_trit(unsigned bits) {
    if (bits == 2)
        return Trit::F;
    else if (bits == 1)
        return Trit::T;
    else
        return Trit::U;
}

unsigned trit_to_int(const Trit &t) {
    if (t == Trit::U)
        return 0;
    else if (t == Trit::T)
        return 1;
    else return 2;
}