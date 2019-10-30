#ifndef PATHTRACER_LIGHT_H
#define PATHTRACER_LIGHT_H


#include "vec3.h"
#include "Color.h"

class Light {
private:
    vec3 position;
    Color color;

public:
    Light(vec3 _position, Color _color) : position(_position), color(_color) {}

    vec3 getPosition() {
        return position;
    }

    Color getColor() {
        return color;
    }
};


#endif
