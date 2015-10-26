#ifndef POINT_INT_H
#define POINT_INT_H

#include "point.h"

class PointInt : public Point {
public:
    PointInt(int x, int y);
    virtual ~PointInt();

    void SetLocation(int x, int y);
};

#endif // POINT_INT_H
