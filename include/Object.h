#ifndef PATHTRACER_OBJECT_H
#define PATHTRACER_OBJECT_H


#include "vec3.h"
#include "Ray.h"


class Object {
private:
    vec3 position;

public:
    virtual void intersect(Ray &ray);
};


#endif
