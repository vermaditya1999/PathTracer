#ifndef PATHTRACER_RENDERER_H
#define PATHTRACER_RENDERER_H

#include "Scene.h"
#include "geometry/Ray.h"

class Renderer {
public:
    virtual void render(Scene scene) = 0;
};

#endif
