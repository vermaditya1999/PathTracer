#ifndef PATHTRACER_SIMPLERENDERER_H
#define PATHTRACER_SIMPLERENDERER_H

#include "Renderer.h"

class SimpleRenderer : public Renderer {
private:
    const double EPS = 1e-5;
    Color tracePath(Ray &ray, int depth, Scene &scene);

public:
    void render(Scene scene) override;

    vec3 reflect(const vec3 &incident, const vec3 &normal);

    vec3 refract(const vec3 &incident, const vec3 &normal, double n1, double n2);

    double reflectance(const vec3 &incident, const vec3 &normal, double n1, double n2);
};

#endif
