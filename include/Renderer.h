#ifndef PATHTRACER_RENDERER_H
#define PATHTRACER_RENDERER_H


#include "Scene.h"
#include "Ray.h"

class Renderer {
private:
    virtual void tracePath(Ray &ray, int depth);

public:
    virtual void render(Scene scene);
};


#endif
