#include "camera/Camera.h"

void Camera::createAxis() {
    w = -g / g.length();

    u = vec3::cross(t, w);
    u.normalize();

    v = vec3::cross(w, u);
}