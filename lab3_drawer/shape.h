//
// Created by Damir on 18.10.2019.
//
#ifndef DRAWER_SHAPE_H
#define DRAWER_SHAPE_H

#include <regex>
#include "bitmap/bitmap_image.hpp"
#include "utility.h"

class Named {
public:
    explicit Named(std::string name = "");

    std::string getName() const;

protected:
    static std::string generateName(const std::string &name);

    void setName(const std::string &_name);

private:
    static std::map<std::string, int> shape_count;
    std::string name;
};

class Colored {
public:
    explicit Colored(int r = 0, int g = 0, int b = 0);

public:
    int getColor(int parameter) const;

    void setColor(int _r, int _g, int _b);

private:
    int r;
    int g;
    int b;
};

class Shape : public Named, public Colored {
public:
    virtual std::vector<int> getParameters() const = 0;

    virtual void setParameters(std::vector<int> params) = 0;

    std::pair<int, int> getCenter() const;

    void setCenter(int x, int y);

    virtual ~Shape() = default;

    virtual std::vector<Segment> getInnerSegments() const = 0;

    virtual std::vector<Segment> getSegments() const = 0;

    virtual double square() const = 0;

private:
    std::pair<int, int> center;
};

class Rectangle : public Shape {
private:
    explicit Rectangle(const std::vector<std::string> &params);

public:
    explicit Rectangle(int w = 0, int h = 0);

    std::vector<int> getParameters() const override;

    void setParameters(std::vector<int> params) override;

    double square() const override;

    std::vector<Segment> getSegments() const override;

    std::vector<Segment> getInnerSegments() const override;

    ~Rectangle() override = default;

private:
    friend class Canvas;

    int h;
    int w;
};

class Triangle : public Shape {
private :
    explicit Triangle(const std::vector<std::string> &params);

public:
    explicit Triangle(int dx1 = 0, int dy1 = 0, int dx2 = 0, int dy2 = 0);

    Triangle(int x, int y, int dx1, int dy1, int dx2, int dy2);

    std::vector<int> getParameters() const override;

    void setParameters(std::vector<int> params) override;

    double square() const override;

    std::vector<Segment> getSegments() const override;

    std::vector<Segment> getInnerSegments() const override;

    ~Triangle() override = default;

private:
    friend class Canvas;

    int dx1;
    int dy1;
    int dx2;
    int dy2;
};

class Circle : public Shape {
private:
    explicit Circle(const std::vector<std::string> &params);

public:
    explicit Circle(int r = 0);

    std::vector<int> getParameters() const override;

    void setParameters(std::vector<int> params) override;

    double square() const override;

    std::vector<Segment> getSegments() const override;

    std::vector<Segment> getInnerSegments() const override;

    ~Circle() override = default;

private:
    friend class Canvas;

    int r;
};


#endif //DRAWER_SHAPE_H
