#ifndef PATHTRACER_RECTANGLE_H
#define PATHTRACER_RECTANGLE_H

#include "Object.h"
#include "Triangle.h"

class Rectangle : public Object {
private:
    Triangle t1, t2;

public:
    Rectangle(const Material *material, const vec3 &p1, const vec3 &p2, const vec3 &p3, const vec3 &p4) :
            Object(material), t1(material, p1, p2, p3), t2(material, p3, p4, p1) {
    }

    void intersect(Ray &ray) override;
};

#endif
