#include "SimpleRenderer.h"

Color SimpleRenderer::tracePath(Ray &ray, int depth, const std::vector<Light *> &lights, Camera *camera) {
    vec3 normal = ray.getNormal();
    vec3 point = ray.getIntersectedPoint();
    vec3 viewDirection = (camera->getPosition() - point).normalize();
    Material mat = ray.getIntersectedObject()->getMaterial();
    double ka = mat.ka;
    double kd = mat.kd;
    double ks = mat.ks;
    double alpha = mat.alpha;
    Color finalColor;

    for (auto light : lights) {
        vec3 lightDirection = (light->getPosition() - point).normalize();

        // Diffused
        finalColor += kd * light->getColor() * std::max(vec3::dot(lightDirection, normal), 0.0);

        // Specular
        vec3 reflectedDirection = (2 * vec3::dot(lightDirection, normal) * normal - lightDirection).normalize();
        finalColor += ks * light->getColor() * std::max(pow(vec3::dot(reflectedDirection, viewDirection), alpha), 0.0);
    }

    finalColor += ka * Color(1.0, 1.0, 1.0);

    return mat.color * finalColor.clamp();
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
                camera->shadePixel(i, j, tracePath(ray, 1, lights, camera));
            } else {
                camera->shadePixel(i, j, Color(0.0));
            }
        }
    }

    camera->saveFile("image");
}
