#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H

#include "Color.h"

class Material {
private:
    Color color;

public:
    explicit Material(const Color &c) : color(c) {}

    const Color &getColor() const {
        return color;
    }
};

#endif
