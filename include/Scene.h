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
    Camera camera;

public:
    Scene() : objects(), lights(), camera() {}

    void setCamera(Camera &_camera);

    void addObject(Object *object);

    void addLight(Light *light);
};


#endif
