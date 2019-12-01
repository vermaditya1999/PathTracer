#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H

#include "Color.h"

class Material {
public:
    enum class Type {
        GLOSSY,
        DIFFUSED,
        DIELECTRIC,
        SPECULARDIFFUSED
    };

    Color color;
    Color emission;
    Type type;

    explicit Material(const Color &color, const Color &emission, Material::Type type)
            : color(color), emission(emission), type(type) {}
};

#endif
