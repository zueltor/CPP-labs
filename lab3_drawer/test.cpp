#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <sstream>
#include <utility>
#include "shape.h"
#include "utility.h"
#include "canvas.h"
#include "parser.h"
#include <cmath>


bool equals(double a, double b) {
    return abs(a - b) < 0.01;
}

TEST_CASE("Names test") {
    std::stringstream out;
    class Rectangle r(12, 7);
    Triangle t(0, 10, 18, 10);
    Circle c(4);
    printOutNames(out, r, c, t, Named("Noname"));
    REQUIRE(out.str() == "Rectangle.1 Circle.1 Triangle.1 Noname.1");
    out.str("");
    printOutNames(out, r, c, t, Circle(3));
    REQUIRE(out.str() == "Rectangle.1 Circle.1 Triangle.1 Circle.2");
    out.str("");
    printOutNames(out, Triangle(1, 2, 3, 4), Circle(3), Named("Noname"));
    REQUIRE(out.str() == "Triangle.2 Circle.3 Noname.2");
}

TEST_CASE("Area test") {

    REQUIRE(equals(totalArea(Triangle(0, 0, 0, 6, 6, 6)), 18.0));
    class Rectangle r(12, 7);
    Triangle t(0, 10, 18, 10);
    Circle c(4);
    REQUIRE(equals(totalArea(c, r), 16 * M_PI + 12 * 7.0));
    REQUIRE(equals(totalArea(t, r), 10 * 9 + 12 * 7.0));
    t.setParameters({0, 3, 0, 6});
    REQUIRE(equals(totalArea(t), 0.0));
    REQUIRE(equals(totalArea(t, t, t, t, t), 0.0));
    r.setParameters({0, 5});
    REQUIRE(equals(totalArea(r), 0.0));
    REQUIRE(equals(totalArea(r, r, r, r, r), 0.0));
    r.setParameters({10, 0});
    REQUIRE(equals(totalArea(r), 0.0));
    REQUIRE(equals(totalArea(r, r, r, r, r), 0.0));
    c.setParameters({0});
    REQUIRE(equals(totalArea(c), 0.0));
    REQUIRE(equals(totalArea(c, c, c, c, c, c, c), 0.0));
    REQUIRE(equals(totalArea(c, r, t, t, r, c, r, t), 0.0));
    t.setParameters({0, 3, -4, 0});
    REQUIRE(equals(totalArea(t, t, t, t, t, t), 3 * 2 * 6.0));
    c.setParameters({7});
    REQUIRE(equals(totalArea(c, c, c, c, c, c), 7 * 7 * M_PI * 6));
    r.setParameters({3, 4});
    REQUIRE(equals(totalArea(r, r, r, r, r), 3 * 4 * 5.0));

}

TEST_CASE("Parser test") {
    Canvas can;
    std::stringstream in;
    in << "800x600\n"
          "Rectangle(700, 320) [300, 200] {42, 204, 29}\n"
          "Circle(500) [0, 860] {31, 14, 59}\n"
          "Triangle(-30, 50, -25, 50) [400, 470] {red}";
    Parser(can, in);
    std::pair<int, int> p(800, 600);
    REQUIRE(can.getCanvasSize() == p);
    p = {300, 200};
    REQUIRE(can.getShape(0)->getCenter() == p);
    p = {0, 860};
    REQUIRE(can.getShape(1)->getCenter() == p);
    p = {400, 470};
    REQUIRE(can.getShape(2)->getCenter() == p);
    std::vector<int> params{700, 320};
    REQUIRE(can.getShape(0)->getParameters() == params);
    params = {500};
    REQUIRE(can.getShape(1)->getParameters() == params);
    params = {-30, 50, -25, 50};
    REQUIRE(can.getShape(2)->getParameters() == params);
    REQUIRE(can.getShape(0)->getColor(2) == 204);
    REQUIRE(can.getShape(0)->getColor(3) == 29);
    REQUIRE(can.getShape(0)->getColor(1) == 42);
    REQUIRE(can.getShape(0)->getColor(2) == 204);
    REQUIRE(can.getShape(0)->getColor(3) == 29);
    REQUIRE(can.getShape(1)->getColor(1) == 31);
    REQUIRE(can.getShape(1)->getColor(2) == 14);
    REQUIRE(can.getShape(1)->getColor(3) == 59);
    REQUIRE(can.getShape(2)->getColor(1) == 255);
    REQUIRE(can.getShape(2)->getColor(2) == 0);
    REQUIRE(can.getShape(2)->getColor(3) == 0);
    in.clear();
    can.clear();
    in << "10x20\n"
          "triAnGle(-30,      50, -25,    50) [-400, 470] {112, 65, 19}\n"
          "ReCtANGle(700,320)[100,-200]{grEEn}\n"
          "CirCLe    (   500)           [-2, -360] {31, 14, 59}\n"
          "TrIangle    (-30, 50, -25, 50) [400,     470]     {Red}     ";
    try {
        Parser(can, in);
        REQUIRE(true);
    }
    catch (...) {
        REQUIRE(false);
    }
    in.clear();
    can.clear();
    in << "800x600\n"
          "Rectangle(-300, 320) [300, 200] {42, 204, 29}";

    try {
        Parser(can, in);
        REQUIRE(false);
    }
    catch (...) {
        REQUIRE(true);
    }
    in.clear();
    can.clear();
    in << "800x600\n"
          "Rectangle(300, 320) [300, 200] {9942, 204, 29}";
    try {
        Parser(can, in);
        REQUIRE(false);
    }
    catch (...) {
        REQUIRE(true);
    }
    in.clear();
    can.clear();
    in << "800x600\n"
          "Circle(500) [0, 860] {42, 999, 29}";
    try {
        Parser(can, in);
        REQUIRE(false);
    }
    catch (...) {
        REQUIRE(true);
    }
    in.clear();
    can.clear();
    in << "800x600\n"
          "Triangle(-30, 50, -25, 50) [400, 470] {112, 65, 9999}";
    try {
        Parser(can, in);
        REQUIRE(false);
    }
    catch (...) {
        REQUIRE(true);
    }
    in.clear();
    can.clear();
    in << "-800x600\n"
          "Triangle(-30, 50, -25, 50) [400, 470] {112, 65, 19}";
    try {
        Parser(can, in);
        REQUIRE(false);
    }
    catch (...) {
        REQUIRE(true);
    }
    in.clear();
    can.clear();
    in << "800x600\n"
          "Test";
    try {
        Parser(can, in);
        REQUIRE(false);
    }
    catch (...) {
        REQUIRE(true);
    }
}

TEST_CASE("Sample draw") {
    int argc = 4;
    const char *argv1[] = {"draw", "test.txt", "-o", "human_outside.bmp"};
    const char *argv2[] = {"draw", "test.txt", "-o", "mario_head.bmp"};
    std::ofstream file("test.txt");
    file << "800x600\n"
            "Rectangle(800, 600) [400, 300] {127, 204, 243}\n"
            "Circle(180) [800, 0] {244, 230, 0}\n"
            "Circle(530) [720, 900] {42, 204, 29}\n"
            "Rectangle(700, 320) [400, 600] {42, 204, 29}\n"
            "Circle(500) [0, 860] {42, 204, 29}\n"
            "Triangle(-30, 50, -25, 50) [400, 470] {112, 65, 150}\n"
            "Triangle(30, 50, 25, 50) [400, 470] {112, 65, 150}\n"
            "Rectangle(6, 60) [400, 440] {112, 65, 150}\n"
            "Triangle(-50, 40, -50, 43) [400, 410] {112, 65, 150}\n"
            "Triangle(50, 40, 50, 43) [400, 410] {112, 65, 150}\n"
            "Triangle(-2, 10, 2, 10) [400, 400] {112, 65, 150}\n"
            "Circle(20) [400, 380] {112, 65, 150}";
    file.close();
    do_main(argc, const_cast<char **>(argv1), true);
    file.open("test.txt");
    file << "1600x700\n"
            "Rectangle(500, 100) [750, 50] {192,55,51}\n"
            "Rectangle(900, 100) [850, 150] {192,55,51}\n"
            "Rectangle(900, 500) [850, 450] {227,197,138}\n"
            "Rectangle(100, 100) [1350, 450] {227,197,138}\n"
            "Rectangle(300, 100) [550, 250] {99,71,58}\n"
            "Rectangle(100, 200) [550, 400] {99,71,58}\n"
            "Rectangle(100, 300) [350, 450] {99,71,58}\n"
            "Rectangle(100, 100) [450, 550] {99,71,58}\n"
            "Rectangle(100, 100) [650, 450] {99,71,58}\n"
            "Rectangle(100, 100) [450, 650] {white}\n"
            "Rectangle(200, 100) [1200, 250] {white}\n"
            "Rectangle(100, 100) [1250, 650] {white}\n"
            "Rectangle(100, 200) [950, 300] {black}\n"
            "Rectangle(100, 100) [1050, 450] {black}\n"
            "Rectangle(400, 100) [1100, 550] {black}";
    file.close();
    do_main(argc, const_cast<char **>(argv2), true);
    REQUIRE(true);
}

TEST_CASE("Pointer test") {
    Circle c(1);
    Shape *sh = &c;
    std::vector<int> params;
    params = sh->getParameters();
    REQUIRE(params[0] == 1);
    REQUIRE(params.size() == 1);
    REQUIRE(equals(sh->square(), M_PI));
    REQUIRE(sh->getName().find("Circle") == 0);
}
