#ifndef PATHTRACER_RAY_H
#define PATHTRACER_RAY_H

#include "Object.h"
#include "vec3.h"

class Object;

class Ray {
private:
    vec3 origin;
    vec3 direction;
    double t;  // Parameter
    Object *intersectedObject;
    vec3 normal;

public:
    explicit Ray(const vec3 _origin, const vec3 _direction, double _t = 0) :
            origin(_origin), direction(_direction), t(_t), intersectedObject(nullptr), normal(0) {}

    const vec3 &getOrigin() const;

    const vec3 &getDirection() const;

    // Returns true if ray has intersected an object.
    bool intersected();

    // Returns the pointer to the intersected object.
    // Returns nullptr if ray has not intersected any object until now.
    Object *getIntersectedObject();

    // Returns the normal to the object at the point of intersection.
    // Returns a null vector if ray has not intersected any object until now.
    vec3 getNormal();

    // Returns the point of intersection.
    // Returns null vector if ray has not intersected any object until now.
    vec3 getIntersectedPoint();

    // Set the ray parameter and intersected object if this is the
    // closest hit in the positive direction of ray.
    void setParameter(Object *object, vec3 _normal, double _t);
};


#endif
