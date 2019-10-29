#ifndef PATHTRACER_RAY_H
#define PATHTRACER_RAY_H


#include "vec3.h"


class Ray {
private:
    vec3 origin;
    vec3 direction;
    double t;  // Parameter

public:
    explicit Ray(const vec3 _origin, const vec3 _direction, double _t) :
            origin(_origin), direction(_direction), t(_t) {}
};


#endif
