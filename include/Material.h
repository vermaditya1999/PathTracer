#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H

#include "Color.h"

class Material {
public:
    Color color;
    double ka;
    double kd;
    double ks;
    double alpha;

    explicit Material(const Color &color, double ka, double kd, double ks, double alpha) : color(color), ka(ka), kd(kd),
                                                                                           ks(ks), alpha(alpha) {}
};

#endif
