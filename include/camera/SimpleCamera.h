#ifndef PATHTRACER_SIMPLECAMERA_H
#define PATHTRACER_SIMPLECAMERA_H

#include "Camera.h"

class SimpleCamera : public Camera {
protected:
    double fd , aper;
public:
    SimpleCamera(vec3 _e, vec3 _g, vec3 _t, double verticalFov, int imageHeight, int imageWidth) :
            Camera(_e, _g, _t, verticalFov, imageHeight, imageWidth) {}
    SimpleCamera(vec3 _e, vec3 _g, vec3 _t, double verticalFov, int imageHeight, int imageWidth , double focus , double aperture) :
            Camera(_e, _g, _t, verticalFov, imageHeight, imageWidth) , fd(focus) , aper(aperture){}
    Ray getRay(int row, int col) const override;

    Ray getRay(int row, int col, int i, int j, int jitterGridSize) const override;

    void shadePixel(int row, int col, Color color) override;
};

#endif
