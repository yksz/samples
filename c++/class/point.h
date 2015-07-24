#ifndef POINT_H
#define POINT_H

#include "movable.h"

class Point : public Movable {
public:
    Point();
    Point(double x, double y);
    Point(const Point&);
    virtual ~Point();

    double getX() const;
    double getY() const;
    void setLocation(double x, double y);

    // Movable
    void move(double x, double y);

protected:
    double m_x;
    double m_y;

private:
    void operator=(const Point&);
};

#endif // POINT_H
