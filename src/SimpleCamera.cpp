#include "camera/SimpleCamera.h"

Ray SimpleCamera::getRay(int row, int col) const {
    vec3 origin = w * -focalDistance +
                  u * (-(double) getImageWidth() / 2 + col + drand48()) +
                  v * ((double) getImageHeight() / 2 - row - drand48());
    vec3 direction(origin - e);
    direction.normalize();

    return Ray(origin, direction, 0.0);
}

void SimpleCamera::shadePixel(int row, int col, Color color) {
    image.setPixel(row, col, color);
}

Ray SimpleCamera::getRay(int row, int col, int i, int j, int gridSize) const {
    double dx = (i + drand48()) / (double) gridSize;
    double dy = (j + drand48()) / (double) gridSize;
    vec3 origin = w * -focalDistance +
                  u * ((-(double) getImageWidth() / 2)*1 + col + dx) +
                  v * (((double) getImageHeight() / 2)*1 - row - dy);
    vec3 direction(origin - e);
//    direction.normalize();

    vec3 point = vec3(0.0);
    if (aper>0) {
        double r1 = drand48();
        double r2 = drand48();

        //Sample Points on disk
        double theta = 2 * M_PI * r1;
        double r = aper * std::sqrt(r2);
        point = vec3(r * std::cos(theta), r * std::sin(theta), 0.0);

        //Transform to world space;
        point = u * point.x + v * point.y;
        point = point;

        //Finding Focal Point in world space;
//        double ft = fd / vec3::dot(direction, w);
//        vec3 pFoc =  + direction * ft;
//
//        direction = pFoc - origin;
//        direction.normalize();
        direction = direction - point;

    }
    direction.normalize();
    return Ray(e + point, direction - point, 0.0);
}
