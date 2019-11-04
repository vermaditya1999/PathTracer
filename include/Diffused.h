#ifndef PATHTRACER_DIFFUSED_H
#define PATHTRACER_DIFFUSED_H

#include "Material.h"

class Diffused : public Material {
public:
    double kd;
    double ka;

    explicit Diffused(const Color &color, double kd, double ka) :
            Material(color, Material::Type::DIFFUSED), kd(kd), ka(ka) {}
};

#endif //PATHTRACER_DIFFUSED_H
