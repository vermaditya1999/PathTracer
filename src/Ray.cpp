#include <iostream>
#include "Ray.h"

bool Ray::isect() {
    return isectObj != nullptr;
}

Object *Ray::getIsectObj() {
    return isectObj;
}

void Ray::setParam(Object *object, vec3 _normal, double _t) {
    if (_t > 0 && (!isect() || _t < t)) {
        isectObj = object;
        normal = _normal;
        t = _t;
    }
}

const vec3 &Ray::getOrigin() const {
    return origin;
}

const vec3 &Ray::getDir() const {
    return dir;
}

vec3 Ray::getNormal() {
    return normal;
}

vec3 Ray::getIsectPt() {
    return origin + dir * t;
}
