#ifndef PATHTRACER_SIMPLECAMERA_H
#define PATHTRACER_SIMPLECAMERA_H

#include "Camera.h"

class SimpleCamera : public Camera {
public:
    SimpleCamera(vec3 _e, vec3 _g, vec3 _t, double _imageDistance, int height, int width) :
            Camera(_e, _g, _t, _imageDistance, height, width) {}

    SimpleCamera(vec3 _e, vec3 _g, vec3 _t, double _imageDistance, Image &_image) :
            Camera(_e, _g, _t, _imageDistance, _image) {}

    Ray getRay(int row, int col) const override;

    void shadePixel(int row, int col, Color color) override;
};

#endif
