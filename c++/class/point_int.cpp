#include "point_int.h"
#include <cstdio>

PointInt::PointInt(int x, int y) : Point(x, y) {}

PointInt::~PointInt() {
    printf("~PointInt()\n");
}

void PointInt::setLocation(int x, int y) {
    Point::setLocation((double) x, (double) y);
}
