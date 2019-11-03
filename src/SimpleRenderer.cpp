#include "SimpleRenderer.h"

Color SimpleRenderer::tracePath(Ray &ray, int depth, Scene &scene) {
    Camera *camera = scene.getCamera();
    auto &lights = scene.getLights();
    auto &objects = scene.getObjects();

    vec3 normal = ray.getNormal();
    vec3 intersectionPoint = ray.getIntersectedPoint();
    vec3 viewDirection = (camera->getPosition() - intersectionPoint).normalize();
    Material mat = ray.getIntersectedObject()->getMaterial();
    double ka = mat.ka;
    double kd = mat.kd;
    double ks = mat.ks;
    double alpha = mat.alpha;
    bool reflective = mat.reflective;
    Color finalColor;

    for (auto light : lights) {
        vec3 lightDirection = (light->getPosition() - intersectionPoint).normalize();
        vec3 reflectedDirection = (2 * vec3::dot(lightDirection, normal) * normal - lightDirection).normalize();

        // Check for shadows
        Ray shadowFeeler(intersectionPoint + lightDirection * 0.001, lightDirection, 0);
        bool shadow = false;
        double lightDistance = (light->getPosition() - intersectionPoint).length();
        for (auto object : objects) {
            object->intersect(shadowFeeler);
            if (shadowFeeler.intersected() &&
                (shadowFeeler.getIntersectedPoint() - intersectionPoint).length() < lightDistance) {
                shadow = true;
                break;
            }
        }

        if (!shadow) {
            // Diffused
            finalColor += kd * light->getColor() * std::max(vec3::dot(lightDirection, normal), 0.0);

            // Specular
            finalColor +=
                    ks * light->getColor() * std::max(pow(vec3::dot(reflectedDirection, viewDirection), alpha), 0.0);
        }

        if (reflective && depth > 0) {
            Ray reflectedRay(intersectionPoint + reflectedDirection * 0.001, reflectedDirection, 0);
            for (auto object : objects) {
                object->intersect(reflectedRay);
            }
            if (reflectedRay.intersected()) {
                finalColor += tracePath(reflectedRay, depth - 1, scene);
            }
        }
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
            Color shade;
            int jitterGridSize = 4;
            for (int _i = 0; _i < jitterGridSize; ++_i) {
                for (int _j = 0; _j < jitterGridSize; ++_j) {
                    Ray ray = camera->getRay(i, j, _i, _j, jitterGridSize);
                    for (auto object : objects) {
                        object->intersect(ray);
                    }
                    if (ray.intersected()) {
                        shade += tracePath(ray, 1, scene);
                    } else {
                        shade += Color(0.0);
                    }
                }
            }
            camera->shadePixel(i, j, shade / (jitterGridSize * jitterGridSize));
        }
    }

    camera->saveFile("image");
}
