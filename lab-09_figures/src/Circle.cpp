#include "Circle.hpp"
#include <cstring>
#include <cstdio>


Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure(id, x, y) {
    this->radius = radius;
    if (label != nullptr) {
        this->label = new char[strlen(label) + 1];
        strcpy(this->label,label);
    } else {
        label = nullptr;
    }
} 

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

void Circle::zoom(int factor) {
    radius = radius * factor;
}

bool Circle::is_inside(int x, int y) const {
    int new_x = x - this->x;
    int new_y = y - this->y;
    return (new_x * new_x + new_y * new_y) <= (radius * radius);
}

Circle& Circle::operator=(const Circle& other) {
    if (this == &other) {
        return *this;
    }
    delete[] label;

    Figure::operator=(other);

    radius = other.radius;

    if (other.label != nullptr) {
        this->label = new char[strlen(other.label) + 1];
        strcpy(label,other.label);
    } else {
        label = nullptr;
    }

    return *this;
}
