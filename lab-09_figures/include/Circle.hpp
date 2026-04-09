#pragma once

#include "Figure.hpp"

class Circle : public Figure {
private:
    int radius;
    char* label;

public:
    Circle(int id, int x, int y, int radius, const char* label);

    Circle& operator=(const Circle& other);
    ~Circle();
    void print() const override;
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;
};
