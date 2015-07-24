#include "point.h"
#include <cstdio>

Point::Point() {
    setLocation(0, 0);
}

Point::Point(double x, double y) {
    setLocation(x, y);
}

Point::Point(const Point& self) {
    setLocation(self.m_x, self.m_y);
}

Point::~Point() {
    printf("~Point()\n");
}

double Point::getX() const {
    return m_x;
}

double Point::getY() const {
    return m_y;
}

void Point::setLocation(double x, double y) {
    m_x = x;
    m_y = y;
}

void Point::move(double x, double y) {
    setLocation(x, y);
}
