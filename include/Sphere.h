#ifndef PATHTRACER_CIRCLE_H
#define PATHTRACER_CIRCLE_H

#include "Object.h"
#include "vec3.h"

class Sphere : public Object {
    vec3 radius, center;
public:
    Sphere(const Material &material, const vec3 &radius, const vec3 &center) : Object(material), radius(radius),
                                                                               center(center) {

    }

    void intersect(Ray &ray) override;
};


#endif //PATHTRACER_CIRCLE_H
