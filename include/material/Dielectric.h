#ifndef PATHTRACER_DIELECTRIC_H
#define PATHTRACER_DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material {
public:
    double eta;

    explicit Dielectric(const Color &color, const Color &emission, double eta) :
            Material(color, emission, Material::Type::DIELECTRIC), eta(eta) {}
};

#endif //PATHTRACER_DIELECTRIC_H
