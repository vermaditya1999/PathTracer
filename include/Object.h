#ifndef PATHTRACER_OBJECT_H
#define PATHTRACER_OBJECT_H


#include "vec3.h"
#include "Ray.h"
#include "Material.h"

class Ray;
class Object {
    Material material;
public:
    explicit Object(const Material &material) : material(material) {}

public:
    virtual void intersect(Ray &ray) = 0;
};

#endif
