#ifndef PATHTRACER_RENDERER_H
#define PATHTRACER_RENDERER_H

#include "Scene.h"
#include "Ray.h"

class Renderer {
protected:
    virtual Color tracePath(Ray &ray, int depth) = 0;

public:
    virtual void render(Scene scene) = 0;
};

#endif
