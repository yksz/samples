#ifndef POINT_H
#define POINT_H

#include "movable.h"

class Point : public Movable {
public:
    Point();
    Point(double x, double y);
    Point(const Point&);
    virtual ~Point();

    double GetX() const;
    double GetY() const;
    void SetLocation(double x, double y);

    // Movable
    void Move(double x, double y);

protected:
    double m_x;
    double m_y;

private:
    void operator=(const Point&);
};

#endif // POINT_H
