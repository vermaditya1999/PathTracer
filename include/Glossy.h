#ifndef PATHTRACER_GLOSSY_H
#define PATHTRACER_GLOSSY_H

#include "Material.h"

class Glossy : public Material {
public:
    double ks;
    double kd;
    double ka;
    double alpha;

    explicit Glossy(const Color &color, double ks, double kd, double ka) :
            Material(color, Material::Type::GLOSSY), ks(ks), kd(kd), ka(ka), alpha(alpha) {}
};

#endif //PATHTRACER_GLOSSY_H
