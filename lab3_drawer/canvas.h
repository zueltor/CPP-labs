//
// Created by Damir on 19.10.2019.
//

#include "shape.h"

#ifndef DRAWER_CONTAINER_H
#define DRAWER_CONTAINER_H


class Canvas {
public:
    void addShape(const std::vector<std::string> &params);

    void setCanvasSize(int h, int w);

    std::pair<int, int> getCanvasSize() const;

    void draw(const std::string &out, bool fill);

    Shape *getShape(int i) const;

    void clear();

private:
    std::vector<std::unique_ptr<Shape>> shapes;
    std::pair<int, int> canvas_size;

};


#endif //DRAWER_CONTAINER_H
