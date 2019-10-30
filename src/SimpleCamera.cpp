#include "SimpleCamera.h"

Ray SimpleCamera::getRay(int row, int col) const {
    // TODO: Implement this function
    return Ray(vec3(), vec3(), 0);
}

void SimpleCamera::shadePixel(int row, int col, Color color) {
    image.setPixel(row, col, color);
}
