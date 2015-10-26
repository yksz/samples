#include "point_int.h"
#include <cstdio>

PointInt::PointInt(int x, int y) : Point(x, y) {}

PointInt::~PointInt() {
    printf("~PointInt: x=%.0f, y=%.0f\n", m_x, m_y);
}

void PointInt::SetLocation(int x, int y) {
    Point::SetLocation((double) x, (double) y);
}
