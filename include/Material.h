#ifndef PATHTRACER_MATERIAL_H
#define PATHTRACER_MATERIAL_H

#include "Color.h"

class Material {
    Color color;
public:
    const Color &getColor() const {
        return color;
    }

public:
    explicit Material(const Color &c) : color(c) {}


};

#endif //PATHTRACER_MATERIAL_H
