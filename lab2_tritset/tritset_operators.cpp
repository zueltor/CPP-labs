#include "tritset.h"

Tproxy Tritset::operator[](size_t i) {
    cur_ind = i;
    Tproxy tp(*this, i);
    return tp;

}

Tritset Tritset::operator|=(const Tritset &ts) {
    size_t n = this->capacity();
    if (n < ts.capacity()) {
        n = ts.capacity();
        this->resize(n);
    }

    for (size_t i = 0; i < n; i++) {
        set[i] = operator_helper(set[i], ts.set[i], '|');
    }
    this->recount_length();
    return *this;
}

Tritset Tritset::operator|(const Tritset &ts) const {
    Tritset ts_new(*this);
    return ts_new |= ts;
}

Tritset &Tritset::operator=(const Tritset &ts) {
    if (this != &ts) {
        Tritset(ts).swap(*this);
    }
    return *this;
}

Tritset &Tritset::operator&=(const Tritset &ts) {
    size_t n = this->capacity();
    if (n < ts.capacity()) {
        n = ts.capacity();
        this->resize(n);
    }

    for (size_t i = 0; i < n; i++) {
        set[i] = operator_helper(set[i], ts.set[i], '&');
    }
    this->recount_length();
    return *this;
}

Tritset Tritset::operator&(const Tritset &ts) const {
    Tritset ts_new(*this);
    return ts_new &= ts;
}

unsigned Tritset::operator_helper(unsigned uint1, unsigned uint2, char op) const {
    unsigned uint_new = 0;
    unsigned u1, u2;
    unsigned j = 0;
    Trit t1, t2;
    unsigned k = 8 * sizeof(unsigned);
    for (; j < k; j += 2) {
        u1 = 0b11 & (uint1 >> j);
        u2 = 0b11 & (uint2 >> j);
        t1 = bits_to_trit(u1);
        t2 = bits_to_trit(u2);
        if (op == '&') {
            uint_new |= (trit_to_int(t1 & t2) << j);
        } else if (op == '|') {
            uint_new |= (trit_to_int(t1 | t2) << j);
        } else if (op == '~')
            uint_new |= (trit_to_int(~t1) << j);
    }
    return uint_new;
}

Tritset Tritset::operator~() const {
    size_t n = this->capacity();
    Tritset t(*this);
    for (size_t i = 0; i < n; i++) {
        t.set[i] = operator_helper(t.set[i], 0, '~');
    }
    t.recount_length();
    return t;
}

bool Tritset::operator==(const Tritset &ts) const {
    if (this->length() != ts.length())
        return false;
    size_t n = this->length() / 4 / sizeof(unsigned) + 1;
    for (size_t i = 0; i < n; i++) {
        if (this->set[i] != ts.set[i])
            return false;
    }
    return true;
}

Tritset &Tritset::operator+=(const Tritset &ts) {
    size_t length = logical_length + ts.logical_length;
    size_t j = 0;
    unsigned n = 4 * sizeof(unsigned);
    size_t i = (logical_length % n == 0) ? size : size - 1;
    n *= 2;
    unsigned shift = (2 * logical_length) % n;
    resize(length);
    size_t ts_size = ts.size - 1;
    if (shift == 0) {
        for (; j < ts.size; j++) {
            set[i] = ts.set[j];
            j++;
        }
    } else {
        set[i] += ts.set[0] << shift;
        i++;
        for (; j < ts_size; j++) {
            set[i] = ts.set[j] >> (n - shift);
            set[i] += ts.set[j + 1] << shift;
        }
        set[i] += ts.set[j] >> (n - shift);
    }
    logical_length = length;
    return *this;
}

Tritset Tritset::operator+(const Tritset &ts) const {
    Tritset tmp(*this);
    tmp += ts;
    return tmp;
}

bool Tritset::operator!=(const Tritset &ts) const {
    return !(*this == ts);
}

Trit Tritset::operator[](size_t i) const {
    return get(i);
}

Tproxy &Tproxy::operator=(const Trit &trit) {
    if (i >= ts->logical_length) {
        if (trit == Trit::U)
            return *this;
        else ts->resize(i + 1);
    }
    if (ts->logical_length <= i && trit != Trit::U) {
        ts->logical_length = i + 1;
    }
    unsigned *pint = ts->set + i / 4 / sizeof(unsigned);
    i = i % (4 * sizeof(unsigned));
    unsigned mask = ~(0b11 << (i * 2));
    unsigned new_uint = mask & (*pint);
    unsigned val = trit_to_int(trit);
    mask = val << (2 * i);
    new_uint |= mask;
    *pint = new_uint;
    if (i + 1 == ts->logical_length)
        this->ts->recount_length();
    return *this;
}

bool Tproxy::operator==(const Tproxy &tp) const {
    return (ts->get(i) == tp.ts->get(tp.i));
}

bool Tproxy::operator==(const Trit &t) const {
    return (ts->get(i) == t);
}

Tproxy &Tproxy::operator=(const Tproxy &tp) {
    Trit trit = tp.ts->get(tp.i);
    *this = trit;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Trit &t) {
    if (t == Trit::F)
        os << "F";
    else if (t == Trit::T)
        os << "T";
    else os << "U";
    return os;
}