#ifndef PATHTRACER_TRIANGLE_H
#define PATHTRACER_TRIANGLE_H

#include "Object.h"

class Triangle : public Object {
private:
    // The points are in the order such that
    // vec3::cross(p3 - p2, p2 - p1) is along the normal
    vec3 p1, p2, p3;

public:
    Triangle(const Material *material, const vec3 &p1, const vec3 &p2, const vec3 &p3) :
            Object(material), p1(p1), p2(p2), p3(p3) {
    }

    void intersect(Ray &ray) override;
};

#endif
