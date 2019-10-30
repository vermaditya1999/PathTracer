#ifndef PATHTRACER_SIMPLECAMERA_H
#define PATHTRACER_SIMPLECAMERA_H


#include "Camera.h"

class SimpleCamera : public Camera {
public:
    Ray getRay(int row, int col) const override;

    void shadePixel(int row, int col, Color color) override;
};


#endif
