#include "point.h"
#include <cstdio>

Point::Point()
        : m_x(0), m_y(0) {
}

Point::Point(double x, double y)
        : m_x(x), m_y(y) {
}

Point::Point(const Point& self)
        : m_x(self.m_x), m_y(self.m_y) {
}

Point::~Point() {
    printf("~Point: x=%.1f, y=%.1f\n", m_x, m_y);
}

double Point::GetX() const {
    return m_x;
}

double Point::GetY() const {
    return m_y;
}

void Point::SetLocation(double x, double y) {
    m_x = x;
    m_y = y;
}

void Point::Move(double x, double y) {
    SetLocation(x, y);
}
