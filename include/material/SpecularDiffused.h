#ifndef PATHTRACER_SPECULARDIFFUSED_H
#define PATHTRACER_SPECULARDIFFUSED_H

#include "Material.h"

class SpecularDiffused : public Material {
public:
    double prefl; // Reflectance when the incident ray is parallel to the surface

    explicit SpecularDiffused(const Color &color, const Color &emission, double prefl) :
            Material(color, emission, Material::Type::SPECULARDIFFUSED), prefl(prefl) {}
};

#endif //PATHTRACER_SPECULARDIFFUSED_H
