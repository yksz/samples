#include <cstdio>
#include "point.h"
#include "point_int.h"

int main(void) {
    PointInt* p1 = new PointInt(1, 2);
    p1->setLocation(3, 4);
    printf("p1(x, y)=(%f, %f)\n", p1->getX(), p1->getY());
    delete p1;

    Point p2 = Point(5, 6);
    Point p3 = Point(p2);
    p3.move(7, 8);
    printf("p2(x, y)=(%f, %f)\n", p2.getX(), p2.getY());
    printf("p3(x, y)=(%f, %f)\n", p3.getX(), p3.getY());
    return 0;
}
