#ifndef ENTITY_H
#define ENTITY_H

#include "Vec3f.h"

class Entity
{
public:
    Entity()
        : position(Point3f(0)) {}
    Entity(Point3f position) 
        : position(position) {}

    virtual Point3f Position() { return position; }
    virtual void SetPosition(const Point3f &new_position) { position = new_position; }
private:
    Point3f position;
};

#endif
