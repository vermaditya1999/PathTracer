#ifndef PATHTRACER_REALISTICRENDERER_H
#define PATHTRACER_REALISTICRENDERER_H

#include "Color.h"
#include "geometry/Ray.h"
#include "Scene.h"
#include "Renderer.h"

class RealisticRenderer : public Renderer {
private:
    static constexpr double EPS = 1e-5;

    static Color tracePath(Ray &ray, int depth, Scene &scene);

    static vec3 reflect(const vec3 &incident, const vec3 &normal);

    static vec3 refract(const vec3 &incident, const vec3 &normal, double n1, double n2);

    static double reflectance(const vec3 &incident, const vec3 &normal, double n1, double n2);

    static vec3 rndHemisphereDir(const vec3 &normal);

public:
    void render(Scene scene) override;
};

#endif
