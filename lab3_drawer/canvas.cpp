//
// Created by Damir on 19.10.2019.
//

#include "canvas.h"

void Canvas::addShape(const std::vector<std::string> &params) {
    std::string shape = params[1];
    to_lower(shape);
    if (shape == "circle") {
        shapes.push_back(std::unique_ptr<Shape>(new Circle(params)));
    } else if (shape == "triangle") {
        shapes.push_back(std::unique_ptr<Shape>(new Triangle(params)));
    } else if (shape == "rectangle") {
        shapes.push_back(std::unique_ptr<Shape>(new Rectangle(params)));
    }
}

void Canvas::setCanvasSize(int h, int w) {
    canvas_size = {h, w};
}

void Canvas::draw(const std::string &out, bool fill) {
    bitmap_image img(canvas_size.first, canvas_size.second);
    std::vector<Segment> segments;
    image_drawer draw(img);
    draw.pen_width(1);
    img.set_all_channels(255, 255, 255);
    for (auto const &shape:shapes) {
        if (fill) {
            segments = shape->getInnerSegments();
        } else {
            segments = shape->getSegments();
        }
        draw.pen_color(shape->getColor(1), shape->getColor(2), shape->getColor(3));
        for (auto &segment : segments) {
            draw.line_segment(segment.start.first, segment.start.second, segment.end.first, segment.end.second);
        }
    }
    if (!out.empty()) {
        img.save_image(out);
    } else {
        img.save_image("example.bmp");
    }
}

Shape *Canvas::getShape(int i) const {
    return shapes[i].get();
}

std::pair<int, int> Canvas::getCanvasSize() const {
    return canvas_size;
}

void Canvas::clear() {
    shapes.clear();
    canvas_size = {0, 0};
}
