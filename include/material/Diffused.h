#ifndef PATHTRACER_DIFFUSED_H
#define PATHTRACER_DIFFUSED_H

#include "Material.h"

class Diffused : public Material {
public:
    double kd;
    double ka;

    explicit Diffused(const Color &color, const Color &emission, double kd, double ka) :
            Material(color, emission, Material::Type::DIFFUSED), kd(kd), ka(ka) {}
};

#endif //PATHTRACER_DIFFUSED_H
