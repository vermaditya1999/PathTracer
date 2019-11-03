#ifndef PATHTRACER_SIMPLERENDERER_H
#define PATHTRACER_SIMPLERENDERER_H

#include "Renderer.h"

class SimpleRenderer : public Renderer {
private:
    Color tracePath(Ray &ray, int depth, Scene &scene);

public:
    void render(Scene scene) override;
};

#endif
