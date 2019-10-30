#include "Ray.h"

bool Ray::intersected() {
    return intersectedObject != nullptr;
}

Object *Ray::getIntersectedObject() {
    return intersectedObject;
}

void Ray::setParameter(Object *object, double _t) {
    if (_t > 0 && (!intersected() || _t < t)) {
        intersectedObject = object;
        t = _t;
    }
}

const vec3 &Ray::getOrigin() const {
    return origin;
}

const vec3 &Ray::getDirection() const {
    return direction;
}
