#ifndef PATHTRACER_SIMPLERENDERER_H
#define PATHTRACER_SIMPLERENDERER_H

#include "Renderer.h"

class SimpleRenderer : public Renderer {
private:
    Color tracePath(Ray &ray, int depth, const std::vector<Light *> &lights, Camera *camera);

public:
    void render(Scene scene) override;
};

#endif
