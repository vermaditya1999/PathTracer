#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H

#include "Color.h"

class Material {
public:
    enum class Type {
        SHINY,
        GLOSSY,
        DIFFUSED,
        DIELECTRIC
    };

    Color color;
    Type type;

    explicit Material(const Color &color, Material::Type type)
            : color(color), type(type) {}
};

#endif
