#include "Ray.h"

bool Ray::intersected() {
    return intersectedObject != nullptr;
}

Object *Ray::getIntersectedObject() {
    return intersectedObject;
}

void Ray::setParameter(Object *object, double _t) {
    if (_t > 0 && _t < t) {
        intersectedObject = object;
        t = _t;
    }
}
