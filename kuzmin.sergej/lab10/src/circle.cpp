#include "circle.h"
#include <cstring>
#include <cstdio>
#include <iostream>

Circle::Circle(int id, int x, int y, int radius, const char* label):
    Figure(id, x, y), radius(radius)
{
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}

Circle::~Circle() {
    delete [] this->label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

static int sqr(int x) {
    return x * x;
}

bool Circle::is_inside(int x, int y) const {
    return sqr(this->x - x) + sqr(this->y - y) <= sqr(this->radius);
}

void Circle::zoom(int factor) {
    radius *= factor;
}
