#ifndef PATHTRACER_SCENE_H
#define PATHTRACER_SCENE_H

#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Light.h"

class Scene {
private:
    std::vector<Object *> objects;
    std::vector<Light *> lights;
    Camera *camera;

public:
    explicit Scene(Camera *_camera) : camera(_camera), objects(), lights() {}

    void addObject(Object *object) {
        objects.push_back(object);
    }

    void addLight(Light *light) {
        lights.push_back(light);
    }

    const std::vector<Object *> &getObjects() const {
        return objects;
    }

    const std::vector<Light *> &getLights() const {
        return lights;
    }

    Camera *getCamera() const {
        return camera;
    }
};

#endif