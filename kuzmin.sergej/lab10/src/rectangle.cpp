#include "rectangle.h"
#include <cstdio>
#include <cstdlib>

Rectangle::Rectangle(int id, int x, int y, int width, int height):
    Figure(id, x, y), width(width), height(height) {}

Rectangle::~Rectangle() {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

static int dbldist(int x, int y) {
    return 2 * abs(x - y);
}

bool Rectangle::is_inside(int x, int y) const {
    return dbldist(x, this->x) <= width && dbldist(y, this->y) <= height;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}
