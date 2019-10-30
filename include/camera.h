
#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H

#include "vec3.h"

class Camera {
    vec3 pos, dir, top;
    int width, height, iDist;
public:
    Camera(int width, int height, int iDist) : width(width), height(height), iDist(iDist) {}
    void inline look_at(const vec3 &_pos, const vec3 &_dir, const vec3 &_top)
    {
        pos = _pos;
        dir = _dir;
        top = _top;
    }

};

#endif
