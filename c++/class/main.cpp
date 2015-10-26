#include <cstdio>
#include "point.h"
#include "point_int.h"

int main(void) {
    PointInt* p1 = new PointInt(1, 2);
    p1->SetLocation(3, 4);
    printf("p1(x, y)=(%.0f, %.0f)\n", p1->GetX(), p1->GetY());
    delete p1;

    Point p2 = Point(5, 6);
    Point p3 = Point(p2);
    p3.Move(7, 8);
    printf("p2(x, y)=(%.1f, %.1f)\n", p2.GetX(), p2.GetY());
    printf("p3(x, y)=(%.1f, %.1f)\n", p3.GetX(), p3.GetY());
    return 0;
}
