#ifndef PATHTRACER_SHINY_H
#define PATHTRACER_SHINY_H

#include "Material.h"

class Shiny : public Material {
public:
    double ks;
    double ka;
    double alpha;

    explicit Shiny(const Color &color, double ks, double ka, double alpha) :
            Material(color, Material::Type::GLOSSY), ks(ks), ka(ka), alpha(alpha) {}
};

#endif //PATHTRACER_SHINY_H
