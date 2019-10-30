#ifndef PATHTRACER_RAY_H
#define PATHTRACER_RAY_H


#include "vec3.h"
#include "Object.h"


class Ray {
private:
    vec3 origin;
    vec3 direction;
    double t;  // Parameter
    Object *intersectedObject;

public:
    explicit Ray(const vec3 _origin, const vec3 _direction, double _t) :
            origin(_origin), direction(_direction), t(_t), intersectedObject(nullptr) {}

    // Returns true if ray has intersected an object.
    bool intersected();

    // Returns the pointer to the intersected object.
    // Returns nullptr if ray has not intersected object until now.
    Object *getIntersectedObject();

    // Set the ray parameter and intersected object if this is the
    // closest hit in the positive direction of ray.
    void setParameter(Object *object, double _t);
};


#endif
