#include <iostream>
#include "Ray.h"

bool Ray::intersected() {
    return intersectedObject != nullptr;
}

Object *Ray::getIntersectedObject() {
    return intersectedObject;
}

void Ray::setParameter(Object *object, vec3 _normal, double _t) {
    if (_t > 0 && (!intersected() || _t < t)) {
        intersectedObject = object;
        normal = _normal;
        t = _t;
    }
}

const vec3 &Ray::getOrigin() const {
    return origin;
}

const vec3 &Ray::getDirection() const {
    return direction;
}

vec3 Ray::getNormal() {
    return normal;
}

vec3 Ray::getIntersectedPoint() {
    return origin + direction * t;
}
