#ifndef PATHTRACER_SCENE_H
#define PATHTRACER_SCENE_H

#include <vector>
#include "geometry/Object.h"
#include "camera/Camera.h"
#include "Light.h"

class Scene {
private:
    Camera *camera;
    Color backgroundColor;
    std::vector<Object *> objects;
    std::vector<Light *> lights;

public:
    explicit Scene(Camera *camera, Color backgroundColor) : camera(camera), backgroundColor(backgroundColor),
                                                            objects(), lights() {}

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

    Color &getBackgroundColor() { return backgroundColor; }
};

#endif