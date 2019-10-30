#ifndef PATHTRACER_CIRCLE_H
#define PATHTRACER_CIRCLE_H

#include "Object.h"
#include "vec3.h"

class Circle: public Object {
    vec3 radius, center;
public:
    Circle(const Material &material, const vec3 &radius, const vec3 &center) : Object(material), radius(radius),
                                                                               center(center) {}
};


#endif //PATHTRACER_CIRCLE_H
