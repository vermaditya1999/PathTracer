#include <debug.h>
#include <iostream>
#include "SimpleRenderer.h"

Color SimpleRenderer::tracePath(Ray &ray, int depth) {
    return Color(1.0, 0.0, 0.0);
}

void SimpleRenderer::render(Scene scene) {
    Camera *camera = scene.getCamera();
    const std::vector<Object *> &objects = scene.getObjects();
    const std::vector<Light *> &lights = scene.getLights();

    int height = camera->getImageHeight();
    int width = camera->getImageWidth();

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Ray ray = camera->getRay(j, i);
            for (Object *object : objects) {
                object->intersect(ray);
            }
            if (ray.intersected()) {
                camera->shadePixel(j, i, tracePath(ray, 1));
            } else {
                camera->shadePixel(j, i, Color(0));
            }
        }
    }

    camera->saveFile("FIRST");
}
