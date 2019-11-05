#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H

#include "vec3.h"
#include "Image.h"
#include "geometry/Ray.h"

class Camera {
protected:
    vec3 e, g, t;
    Image image;

    vec3 u, v, w;
    double focalDistance;

    void createAxis();

public:
    Camera(vec3 _e, vec3 _g, vec3 _t, double verticalFov, int imageHeight, int imageWidth) :
            e(_e), g(_g), t(_t), image(imageHeight, imageWidth) {
        createAxis();
        focalDistance = imageHeight / (2.0 * tan(verticalFov * M_PI / 360.0));
//        debug("Focal Distance: %f", focalDistance);
    }

    int getImageHeight() const {
        return image.getHeight();
    }

    int getImageWidth() const {
        return image.getWidth();
    }

    vec3 getPosition() const {
        return e;
    };

    void saveFile(const std::string &file) const {
        image.savePPM(file + ".ppm");
    }

    virtual Ray getRay(int row, int col) const = 0;

    // Jittered super sampling
    virtual Ray getRay(int row, int col, int i, int j, int jitterGridSize) const = 0;

    virtual void shadePixel(int row, int col, Color color) = 0;
};


#endif
