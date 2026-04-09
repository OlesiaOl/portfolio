#include "Rectangle.hpp"
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

void Rectangle::zoom(int factor) {
    width = width * factor;
    height = height * factor;
}

bool Rectangle::is_inside(int x, int y) const {
    return (((this->x - (width)/2) <= x) &&
    ((this->x + (width)/2) >= x) &&
    ((this->y - (height)/2) <= y ) &&
    ((this->y + (height)/2) >= y));
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this == &other) {
        return *this;
    }

    Figure::operator=(other);
    width = other.width;
    height = other.width;

    return *this;
}
