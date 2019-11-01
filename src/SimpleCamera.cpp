#include "SimpleCamera.h"

Ray SimpleCamera::getRay(int row, int col) const {
    vec3 origin = w * -focalDistance +
                  u * (-(double) getImageWidth() / 2 + col + 0.5) +
                  v * ((double) getImageHeight() / 2 - row - 0.5);
    vec3 direction(origin - e);
    direction.normalize();

    return Ray(origin, direction, 0.0);
}

void SimpleCamera::shadePixel(int row, int col, Color color) {
    image.setPixel(row, col, color);
}
