#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H


#include "vec3.h"
#include "Image.h"
#include "Ray.h"

class Camera {
private:
    vec3 eye;
    vec3 gaze;
    vec3 top;
    double imageDistance;
    Image image;

public:
    Camera(vec3 _eye, vec3 _gaze, vec3 _top, double _imageDistance, Image &_image) :
            eye(_eye), gaze(_gaze), top(_top), imageDistance(_imageDistance), image(_image) {}

    int getImageHeight() const {
        return image.getHeight();
    }

    int getImageWidth() const {
        return image.getWidth();
    }

    virtual Ray getRay(int row, int col) const;

    virtual void shadePixel(int row, int col, Color color);
};


#endif
