#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H

#include "vec3.h"
#include "Image.h"
#include "Ray.h"

class Camera {
protected:
    vec3 e, g, t;
    vec3 u, v, w;
    double imageDistance;
    Image image;

    void createAxis() {
        w = -g / g.length();

        u = vec3::cross(t, w);
        u.normalize();

        v = vec3::cross(w, u);
    }

public:
    Camera(vec3 _e, vec3 _g, vec3 _t, double _imageDistance, int height, int width) :
            e(_e), g(_g), t(_t), imageDistance(_imageDistance), image(height, width) {
        createAxis();
    }

    Camera(vec3 _e, vec3 _g, vec3 _t, double _imageDistance, Image &_image) :
            e(_e), g(_g), t(_t), imageDistance(_imageDistance), image(_image) {
        createAxis();
    }

    int getImageHeight() const {
        return image.getHeight();
    }

    int getImageWidth() const {
        return image.getWidth();
    }

    void saveFile(std::string file) const {
        image.savePPM(file + ".ppm");
    }

    virtual Ray getRay(int row, int col) const = 0;

    virtual void shadePixel(int row, int col, Color color) = 0;
};


#endif
