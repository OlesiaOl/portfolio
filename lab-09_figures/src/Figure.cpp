#include "Figure.hpp"

Figure::Figure(int id, int x, int y) : id(id), x(x), y(y) {}

void Figure::move(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

Figure& Figure::operator=(const Figure& other) {
    x = other.x;
    y = other.y;
    return *this;
}

int Figure::get_id() const {
    return id;
}
