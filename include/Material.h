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
    bool reflective;

    explicit Material(const Color &color, double ka, double kd, double ks, double alpha, bool reflective = false)
            : color(color), ka(ka), kd(kd),
              ks(ks), alpha(alpha), reflective(reflective) {}
};

#endif
