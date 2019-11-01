#ifndef PATHTRACER_SIMPLECAMERA_H
#define PATHTRACER_SIMPLECAMERA_H

#include "Camera.h"

class SimpleCamera : public Camera {
public:
    SimpleCamera(vec3 _e, vec3 _g, vec3 _t, double verticalFov, int imageHeight, int imageWidth) :
            Camera(_e, _g, _t, verticalFov, imageHeight, imageWidth) {}

    Ray getRay(int row, int col) const override;

    void shadePixel(int row, int col, Color color) override;
};

#endif
