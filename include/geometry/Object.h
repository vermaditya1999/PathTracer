#ifndef PATHTRACER_OBJECT_H
#define PATHTRACER_OBJECT_H

#include "vec3.h"
#include "Ray.h"
#include "material/Material.h"

class Ray;

class Object {
private:
    static int MAX_OBJ_ID;
    const Material *material;

public:
    explicit Object(const Material *material) : material(material), OBJ_ID(++MAX_OBJ_ID) {}

    virtual void intersect(Ray &ray) = 0;

    const Material *getMaterial() const {
        return material;
    }

    const int OBJ_ID;
};

#endif
