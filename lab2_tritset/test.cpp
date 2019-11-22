#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <sstream>
#include "tritset.h"

TEST_CASE("Test") {
    std::stringstream out;
    Tritset set(3);
    unsigned n = set.capacity();
    unsigned length = set.length();
    unsigned fcount = set.cardinality(Trit::F);
    unsigned tcount = set.cardinality(Trit::T);
    unsigned ucount = set.cardinality(Trit::U);
    REQUIRE(n == 1);
    REQUIRE(length == 0);
    REQUIRE(fcount == 0);
    REQUIRE(tcount == 0);
    REQUIRE(ucount == 0);
    set[1] = Trit::T;
    n = set.capacity();
    length = set.length();
    fcount = set.cardinality(Trit::F);
    tcount = set.cardinality(Trit::T);
    ucount = set.cardinality(Trit::U);
    REQUIRE (n == 1);
    REQUIRE(length == 2);
    REQUIRE(fcount == 0);
    REQUIRE(tcount == 1);
    REQUIRE(ucount == 1);
    set[2] = Trit::F;
    n = set.capacity();
    length = set.length();
    fcount = set.cardinality(Trit::F);
    tcount = set.cardinality(Trit::T);
    ucount = set.cardinality(Trit::U);
    REQUIRE (n == 1);
    REQUIRE(length == 3);
    REQUIRE(fcount == 1);//
    REQUIRE(tcount == 1);
    REQUIRE(ucount == 1);
    set[3] = Trit::F;
    n = set.capacity();
    length = set.length();
    fcount = set.cardinality(Trit::F);
    tcount = set.cardinality(Trit::T);
    ucount = set.cardinality(Trit::U);
    set.print(out);
    REQUIRE (n == 1);
    REQUIRE(length == 4);
    REQUIRE(fcount == 2);
    REQUIRE(tcount == 1);
    REQUIRE(ucount == 1);
    REQUIRE(out.str() == "UTFF\n");
    out.str("");
    set[19] = Trit::F;
    n = set.capacity();
    length = set.length();
    fcount = set.cardinality(Trit::F);
    tcount = set.cardinality(Trit::T);
    ucount = set.cardinality(Trit::U);
    REQUIRE (n == 2);
    REQUIRE(length == 20);
    REQUIRE(fcount == 3);
    REQUIRE(tcount == 1);
    REQUIRE(ucount == 16);
    set[15] = Trit::T;
    set.shrink();
    n = set.capacity();
    length = set.length();
    fcount = set.cardinality(Trit::F);
    tcount = set.cardinality(Trit::T);
    ucount = set.cardinality(Trit::U);
    REQUIRE (n == 1);
    REQUIRE(length == 16);
    REQUIRE(fcount == 2);
    REQUIRE(tcount == 2);
    REQUIRE(ucount == 12);
    set[1] = Trit::F; // T->F
    set[3] = Trit::U; // F->U
    n = set.capacity();
    length = set.length();
    fcount = set.cardinality(Trit::F);
    tcount = set.cardinality(Trit::T);
    ucount = set.cardinality(Trit::U);
    REQUIRE (n == 1);
    REQUIRE(length == 16);
    REQUIRE(fcount == 2);
    REQUIRE(tcount == 1);
    REQUIRE(ucount == 13);

    set[22] = Trit::T;
    length = set.length();

    REQUIRE(length == 23);
    set[12] = Trit::F;
    set.shrink();
    length = set.length();
    REQUIRE(length == 13);
    set[39] = Trit::F;
    set[208] = Trit::T;
    set.trim(40);
    length = set.length();
    REQUIRE(length == 40);


    set[4] = Trit::T;
    set[5] = Trit::F;
    set[5] = set[4];
    REQUIRE(set[5] == Trit::T);
    set.shrink();
    set = {Trit::T, Trit::F, Trit::T, Trit::U, Trit::U, Trit::U};

    set.print(out);
    REQUIRE(out.str() == "TFT\n");
    out.str("");
    Tritset s2(4);
    s2[0] = Trit::T;
    s2[1] = Trit::T;
    s2[2] = Trit::U;
    s2[3] = Trit::F;
    s2[4] = Trit::T;
    s2.print(out);
    REQUIRE(out.str() == "TTUFT\n");
    out.str("");

    Tritset s3 = set & s2;
    s3.print(out);
    REQUIRE(out.str() == "TFUF\n");
    out.str("");

    s3 = set | s2;
    s3.print(out);
    REQUIRE(out.str() == "TTTUT\n");
    out.str("");

    s3 = set + s2;
    s3.print(out);
    REQUIRE(out.str() == "TFTTTUFT\n");
    out.str("");
    s3 = ~s3;
    s3.print(out);
    REQUIRE(out.str() == "FTFFFUTF\n");
    out.str("");

    Tritset s4{Trit::T, Trit::F, Trit::T, Trit::U, Trit::F, Trit::U, Trit::U};
    s4.print(out);
    REQUIRE(out.str() == "TFTUF\n");
    out.str("");

    set = {Trit::T, Trit::F};
    s2 = {Trit::U, Trit::F};
    s3 = {Trit::U, Trit::T};
    s4 += set + s2 + s3;
    s4.print(out);
    REQUIRE(out.str() == "TFTUFTFUFUT\n");
    out.str("");
    set |= s3;
    s3 &= s2;
    s2 = ~s2;
    s4 = set + s2 + s3;
    s4.print(out);
    REQUIRE(out.str() == "TTUTUF\n");
    out.str("");
    set = ~s4 + Tritset{Trit::T, Trit::U, Trit::T};
    set.print(out);
    REQUIRE(out.str() == "FFUFUTTUT\n");
    out.str("");

    set.trim(2);
    set += Tritset{Trit::U, Trit::T, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U,
                   Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U};
    set.print(out);
    REQUIRE(out.str() == "FFUT\n");
    out.str("");

    s2 = {Trit::U, Trit::T, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::F}; //8
    s3 = {Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F,
          Trit::T}; //13
    set = s2 + s3;
    set.print(out);
    REQUIRE(out.str() == "UTUUUUUFTFTFTFTFTFTFT\n");
    out.str("");

    REQUIRE(s2 != s3);

    s2 = {Trit::U, Trit::T, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U,
          Trit::U, Trit::U, Trit::U, Trit::U, Trit::T}; //17
    s3 = {Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F, Trit::T, Trit::F,
          Trit::T, Trit::F, Trit::T, Trit::F, Trit::T}; //17
    set = s2 + s3;
    set.print(out);
    REQUIRE(out.str() == "UTUUUUUUUUUUUUUUTTFTFTFTFTFTFTFTFT\n");
    out.str("");

    REQUIRE(s2 != s3);

    s2 = {Trit::U, Trit::T, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U, Trit::U,
          Trit::U, Trit::U, Trit::T}; //15
    s3 = {Trit::T}; //1
    set = s2 + s3;
    set.print(out);
    REQUIRE(out.str() == "UTUUUUUUUUUUUUTT\n");
    out.str("");

    REQUIRE(s2 != s3);

    s2 = {Trit::U, Trit::T, Trit::U, Trit::U, Trit::U};
    s3 = {Trit::U, Trit::T};

    REQUIRE(s2 == s3);

    s2[1000] = Trit::U;

    REQUIRE(s2 == s3);

    s2[4] = Trit::F;

    REQUIRE(s2 != s3);

    Tritset s5;

    REQUIRE(s5.length() == 0);
    REQUIRE(s5.capacity() == 0);
    REQUIRE(s5.get(123) == Trit::U);
    REQUIRE(s5[443] == Trit::U);

    s5[99] = Trit::T;
    REQUIRE(s5.length() == 100);
    s5.shrink();
    REQUIRE(s5.length() == 100);
    s5[0] = Trit::T;
    s5.shrink();
    REQUIRE(s5.length() == 1);

    s3 = {Trit::F, Trit::T, Trit::T};
    s5 = s3;
    REQUIRE(s5[1] == Trit::T);
    REQUIRE(s5.length() == 3);


}

TEST_CASE("Cardinality") {
    std::stringstream out;
    Tritset s1 = {Trit::U, Trit::T, Trit::F, Trit::T};
    Tritset s2 = {Trit::T, Trit::U, Trit::U, Trit::F};
    std::unordered_map<Trit, size_t> map = {{Trit::T, 2},
                                              {Trit::U, 1},
                                              {Trit::F, 1}};
    REQUIRE(s1.cardinality(Trit::T) == 2);
    REQUIRE(s1.cardinality(Trit::U) == 1);
    REQUIRE(s1.cardinality(Trit::F) == 1);
    REQUIRE(s1.cardinality() == map);
    map = {{Trit::T, 1},
           {Trit::U, 2},
           {Trit::F, 1}};
    REQUIRE(s2.cardinality(Trit::T) == 1);
    REQUIRE(s2.cardinality(Trit::U) == 2);
    REQUIRE(s2.cardinality(Trit::F) == 1);
    REQUIRE(s2.cardinality() == map);
    s1 += s2;
    map = {{Trit::T, 3},
           {Trit::U, 3},
           {Trit::F, 2}};
    REQUIRE(s1.cardinality(Trit::T) == 3);
    REQUIRE(s1.cardinality(Trit::U) == 3);
    REQUIRE(s1.cardinality(Trit::F) == 2);
    REQUIRE(s1.cardinality() == map);
}
