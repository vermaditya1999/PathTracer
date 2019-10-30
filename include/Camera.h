#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H


#include "vec3.h"
#include "Image.h"
#include "Ray.h"

class Camera {
protected:
    vec3 eye, gaze, top;
    double imageDistance;
    Image image;

public:
    Camera(vec3 _eye, vec3 _gaze, vec3 _top, double _imageDistance, int height, int width) :
            eye(_eye), gaze(_gaze), top(_top), imageDistance(_imageDistance), image(height, width) {}

    Camera(vec3 _eye, vec3 _gaze, vec3 _top, double _imageDistance, Image &_image) :
            eye(_eye), gaze(_gaze), top(_top), imageDistance(_imageDistance), image(_image) {}

    int getImageHeight() const {
        return image.getHeight();
    }

    int getImageWidth() const {
        return image.getWidth();
    }

    virtual Ray getRay(int row, int col) const = 0;

    virtual void shadePixel(int row, int col, Color color) = 0;
};


#endif
