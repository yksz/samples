#ifndef MOVABLE_H
#define MOVABLE_H

class Movable {
public:
    virtual ~Movable() {};
    virtual void Move(double x, double y) = 0;
};

#endif // MOVABLE_H
