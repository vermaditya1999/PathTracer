#include <debug.h>
#include <iostream>
#include "SimpleRenderer.h"

#include "debug.h"

Color SimpleRenderer::tracePath(Ray &ray, int depth) {
    return Color(1.0, 0.0, 0.0);
}

void SimpleRenderer::render(Scene scene) {
    Camera *camera = scene.getCamera();
    const std::vector<Object *> &objects = scene.getObjects();
    const std::vector<Light *> &lights = scene.getLights();

    int height = camera->getImageHeight();
    int width = camera->getImageWidth();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Ray ray = camera->getRay(i, j);
            for (auto object : objects) {
                object->intersect(ray);
            }
            if (ray.intersected()) {
                camera->shadePixel(i, j, tracePath(ray, 1));
            } else {
                camera->shadePixel(i, j, Color(0));
            }
        }
    }

    camera->saveFile("FIRST");
}
