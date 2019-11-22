#include "tritset.h"

size_t uintsize(unsigned i) {
    unsigned n = 4 * sizeof(unsigned);
    return (i % n == 0) ? i / n : i / n + 1;
}

Tritset::Tritset(size_t _size) : size(uintsize(_size)), cur_ind(0), logical_length(0),
                                 set(new unsigned[uintsize(_size)]) {
    for (size_t i = 0; i < size; i++) {
        set[i] = 0;
    }
}

Tritset::Tritset(const Tritset &ts) : size(ts.size), cur_ind(ts.cur_ind),
                                      logical_length(ts.logical_length), set(new unsigned[ts.size]) {
    for (size_t i = 0; i < size; i++) {
        set[i] = ts.set[i];
    }
}

Tritset::Tritset(std::initializer_list<Trit> il)
        : set(new unsigned[uintsize(il.size())]), size(uintsize(il.size())), cur_ind(0), logical_length(0) {
    size_t i = 0;
    unsigned bits = 0;
    unsigned shift = 0;
    unsigned uint = 0;
    unsigned n = 8 * sizeof(unsigned);
    for (const auto t:il) {
        bits = trit_to_int(t) << shift;
        uint |= bits;
        shift += 2;
        if (shift == n) {
            shift = 0;
            set[i] = uint;
            i++;
            uint = 0;
        }
    }
    if (shift != 0) {
        set[i] = uint;
    }
    recount_length();
}

Tritset::~Tritset() {
    delete[] set;
    set = nullptr;
}

void Tritset::shrink() {
    resize(cur_ind + 1);
    recount_length();
}


void Tritset::swap(Tritset &t) {
    std::swap(t.set, set);
    std::swap(t.size, size);
    std::swap(t.logical_length, logical_length);
}

void Tritset::resize(size_t length) {
    Tritset t(length);
    size_t nsize = uintsize(length);
    size_t n = (length < logical_length) ? nsize : size;
    t.cur_ind = cur_ind;
    size_t i = 0;
    for (; i < n; i++) {
        t.set[i] = set[i];
    }
    unsigned m = 4 * sizeof(unsigned);
    if (length < logical_length && length % m != 0) {
        length = length % (m);
        unsigned mask = ~((~0) << (length * 2));
        i--;
        t.set[i] &= mask;
        t.recount_length();
    }
    swap(t);
}

size_t Tritset::capacity() const {
    return size;
}

void Tritset::print(std::ostream &output) const {
    for (auto const &t:*this) {
        output << t;
    }
    output << std::endl;
}

void Tritset::recount_length() {
    size_t i = this->size - 1;
    while (set[i] == 0 && i-- > 0) {}
    size_t l = (i + 1) * 4 * sizeof(unsigned) - 1;
    unsigned n = set[i];
    unsigned mask = 0b11 << (8 * sizeof(unsigned) - 2);
    while (!(n & mask) && mask) {
        mask = mask >> 2;
        l--;
    }
    logical_length = l + 1;
}

size_t Tritset::cardinality(const Trit &value) const {
    size_t n = this->length();
    unsigned val = trit_to_int(value);
    unsigned mask = 0b11;
    unsigned shift_val = val;
    size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        if ((mask & set[i / 4 / sizeof(unsigned)]) == shift_val) {
            count++;
        }
        mask = mask << 2;
        shift_val = shift_val << 2;
        if (mask == 0) {
            mask = 0b11;
            shift_val = val;
        }
    }
    return count;
}

size_t Tritset::length() const {
    return logical_length;
}

Trit Tritset::get(size_t i) const {
    if (i >= logical_length)
        return Trit::U;
    unsigned n = i / 4 / sizeof(unsigned);
    i = i % (4 * sizeof(unsigned));
    unsigned mask = 0b11 << (2 * i);
    unsigned bits = (mask & set[n]) >> (2 * i);
    return bits_to_trit(bits);
}

Iterator Tritset::begin() const {
    return Iterator(set, 0);
}

Iterator Tritset::end() const {
    return Iterator(set, logical_length);
}

void Tritset::trim(size_t length) {
    resize(length);
}

Tproxy::Tproxy(Tritset &ts, size_t i) : i(i), ts(&ts) {}

std::unordered_map<Trit, size_t> Tritset::cardinality() const {
    std::unordered_map<Trit, size_t> card = {{Trit::T, 0},
                                               {Trit::F, 0},
                                               {Trit::U, 0}};
    size_t n = this->length();
    unsigned valt = trit_to_int(Trit::T);
    unsigned valf = trit_to_int(Trit::F);
    unsigned valu = trit_to_int(Trit::U);
    unsigned mask = 0b11;
    unsigned shift = 0;
    unsigned m = 4 * sizeof(unsigned);
    for (size_t i = 0; i < n; i++) {
        if ((mask & set[i / m]) == valt << shift) {
            card[Trit::T]++;
        } else if ((mask & set[i / m]) == valf << shift) {
            card[Trit::F]++;
        } else if ((mask & set[i / m]) == valu << shift) {
            card[Trit::U]++;
        }
        mask = mask << 2;
        shift += 2;
        if (mask == 0) {
            mask = 0b11;
            shift = 0;
        }
    }
    return card;
}

