#include "SimpleCamera.h"

Ray SimpleCamera::getRay(int row, int col) const {
    vec3 origin = w * -imageDistance +
                  u * (-(double) getImageHeight() / 2 + (col - 1) + 0.5) +
                  v * ((double) getImageWidth() / 2 - (row - 1) - 0.5);

    vec3 direction(origin - e);
    direction.normalize();

    double t = 0.0;

    return Ray(origin, direction, t);
}

void SimpleCamera::shadePixel(int row, int col, Color color) {
    image.setPixel(row, col, color);
}
