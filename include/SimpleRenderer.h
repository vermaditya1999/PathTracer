#ifndef PATHTRACER_SIMPLERENDERER_H
#define PATHTRACER_SIMPLERENDERER_H

#include "Renderer.h"

class SimpleRenderer : public Renderer {
protected:
    Color tracePath(Ray &ray, int depth) override;

public:
    void render(Scene scene) override;
};

#endif
