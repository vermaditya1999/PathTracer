#ifndef PATHTRACER_SIMPLERENDERER_H
#define PATHTRACER_SIMPLERENDERER_H

#include "Renderer.h"

class SimpleRenderer : public Renderer {
private:
    static constexpr double EPS = 1e-5;

    static Color tracePath(Ray &ray, int depth, Scene &scene);

    static vec3 reflect(const vec3 &incident, const vec3 &normal);

    static vec3 refract(const vec3 &incident, const vec3 &normal, double n1, double n2);

    static double reflectance(const vec3 &incident, const vec3 &normal, double n1, double n2);

public:
    void render(Scene scene) override;
};

#endif
