// tracePath method
Color tracePath(Ray& ray, int depth) {
    if (depth <= 0) {
        return Color.BLACK;
    }

    for (Object* object : objects) {
        object->intersect(ray);
    }

    Object* object;
    Material* material;
    if (ray.hitSomething()) {
        object = ray.getIsectObj();
        material = object.getMaterial();
    } else {
        return scene.getBackgroundColor();
    }

    // create new ray, return color using rendering equation
}

// An Object's sample intersect method
void intersect(Ray& ray) {
    double origin = ray.getOrigin();
    double dir = ray.getDir();
    double t = 0;

    // Perform intersection

    ray.setParameter(*this, t);
}

// Ray setParameter method
void setParam(Object* object, double _t) {
    if (_t > 0 && _t < t) {
        IntersectedObject = object;
        t = _t;
    }
}

// Material types
SHINY (ks, ka)
GLOSSY (ks, kd, ka)
DIFFUSED (kd, ka)
DIELECTRIC