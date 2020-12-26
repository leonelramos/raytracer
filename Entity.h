#ifndef ENTITY_H
#define ENTITY_H

#include "Vec3.h"

class Entity
{
public:
    Entity()
        : position(Point3(0)) {}
    Entity(Point3 position) 
        : position(position) {}

    virtual Point3 Position() { return position; }
    virtual void SetPosition(const Point3 &new_position) { position = new_position; }
private:
    Point3 position;
};

#endif
