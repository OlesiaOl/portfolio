#include "Figure.hpp"

class Rectangle : public Figure {
private:
    int width;
    int height;

public:
    Rectangle(int id, int x, int y, int width, int height);
    void print() const override;
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;
    virtual ~Rectangle() = default;
    virtual Rectangle& operator=(const Rectangle& other);

};
