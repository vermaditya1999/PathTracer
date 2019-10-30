#include "Scene.h"

void Scene::setCamera(Camera &_camera) {
    camera = _camera;
}

void Scene::addObject(Object *object) {
    objects.push_back(object);
}

void Scene::addLight(Light *light) {
    lights.push_back(light);
}
