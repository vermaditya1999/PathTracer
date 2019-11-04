#ifndef PATHTRACER_RAY_H
#define PATHTRACER_RAY_H

#include "Object.h"
#include "vec3.h"

class Object;

class Ray {
private:
    vec3 origin;
    vec3 dir;
    double t;  // Parameter
    Object *isectObj;
    vec3 normal;

public:
    explicit Ray(const vec3 _origin, const vec3 _direction, double _t = 0) :
            origin(_origin), dir(_direction), t(_t), isectObj(nullptr), normal(0) {}

    const vec3 &getOrigin() const;

    const vec3 &getDir() const;

    // Returns true if ray has intersected an object.
    bool isect();

    // Returns the pointer to the intersected object.
    // Returns nullptr if ray has not intersected any object until now.
    Object *getIsectObj();

    // Returns the normal to the object at the point of intersection.
    // Returns a null vector if ray has not intersected any object until now.
    vec3 getNormal();

    // Returns the point of intersection.
    // Returns null vector if ray has not intersected any object until now.
    vec3 getIsectPt();

    // Set the ray parameter and intersected object if this is the
    // closest hit in the positive dir of ray.
    void setParam(Object *object, vec3 _normal, double _t);
};


#endif
