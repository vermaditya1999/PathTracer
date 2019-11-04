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
    bool dielectric;
    double eta;

    explicit Material(const Color &color, double ka, double kd, double ks, double alpha, bool dielectric = false,
                      double eta = 0)
            : color(color), ka(ka), kd(kd),
              ks(ks), alpha(alpha), dielectric(dielectric), eta(eta) {}
};

#endif
