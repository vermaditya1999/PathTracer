#ifndef PATHTRACER_CIRCLE_H
#define PATHTRACER_CIRCLE_H

#include "Object.h"
#include "vec3.h"

class Sphere: public Object {
private:
    vec3 center;
    double radius;

public:
    Sphere(const Material *material, double radius, const vec3 &center) : Object(material), radius(radius),
                                                                          center(center) {}

    void intersect(Ray &ray) override;
};

#endif
