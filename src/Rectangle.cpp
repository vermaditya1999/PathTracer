#include "geometry/Rectangle.h"

void Rectangle::intersect(Ray &ray) {
    t1.intersect(ray);
    t2.intersect(ray);
}
