#ifndef PATHTRACER_GLOSSY_H
#define PATHTRACER_GLOSSY_H

#include "Material.h"

class Glossy : public Material {
public:
    double ks;
    double kd;
    double ka;
    double alpha;

    explicit Glossy(const Color &color, const Color &emission, double ks, double kd, double ka, double alpha) :
            Material(color, emission, Material::Type::GLOSSY), ks(ks), kd(kd), ka(ka), alpha(alpha) {}
};

#endif //PATHTRACER_GLOSSY_H
