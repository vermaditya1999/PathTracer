#include <SimpleCamera.h>
#include "SimpleRenderer.h"

/*
 * Check the intersection of ray with objects in the scene and
 * return the shade color.
 *
 * Effects: Reflection, Total Internal Reflection, Refraction,
 *          Dielectric Reflection and Refraction using Schlick's
 *          approximation for Fresnel's equations.
 * */
Color SimpleRenderer::tracePath(Ray &ray, int depth, Scene &scene) {
    auto &objects = scene.getObjects();

    for (auto &object: objects) {
        object->intersect(ray);
    }

    if (!ray.intersected()) {
        return scene.getBackgroundColor();
    }

    Camera *camera = scene.getCamera();
    auto &lights = scene.getLights();

    vec3 normal = ray.getNormal();
    vec3 intersectionPoint = ray.getIntersectedPoint();
    vec3 incident = ray.getDirection();

    Material mat = ray.getIntersectedObject()->getMaterial();
    double ka = mat.ka;
    double kd = mat.kd;
    double ks = mat.ks;
    double alpha = mat.alpha;
    bool dielectric = mat.dielectric;
    double eta = mat.eta;

    Color shade;

    if (!dielectric) {
        vec3 viewDir = (camera->getPosition() - intersectionPoint).normalize();
        for (auto light : lights) {

            vec3 lightDir = (light->getPosition() - intersectionPoint).normalize();
            vec3 reflectedDirection = (2 * vec3::dot(lightDir, normal) * normal - lightDir).normalize();

            // Check for shadows
            Ray shadowFeeler(intersectionPoint + lightDir * EPS, lightDir);
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
                shade += kd * light->getColor() * std::max(vec3::dot(lightDir, normal), 0.0);

                // Specular
                shade +=
                        ks * light->getColor() *
                        std::max(pow(vec3::dot(reflectedDirection, viewDir), alpha), 0.0);
            }
        }

        shade += Color(ka);
    }

    if (dielectric && depth > 0) {
        double R;
        vec3 reflectDir, refractDir;
        Color reflectCol, refractCol;

        if (vec3::dot(incident, normal) < 0) {
            // Ray is going in the object
            reflectDir = reflect(incident, normal);
            refractDir = refract(incident, normal, 1.0, eta);

            Ray reflectRay(intersectionPoint + reflectDir * EPS, reflectDir);
            Ray refractRay(intersectionPoint + refractDir * EPS, refractDir);

            reflectCol = tracePath(reflectRay, depth - 1, scene);
            refractCol = tracePath(refractRay, depth - 1, scene);

            R = reflectance(incident, normal, 1.0, eta);
        } else {
            // Ray is going out from the object
            reflectDir = reflect(incident, -normal);
            refractDir = refract(incident, -normal, eta, 1.0);

            if (refractDir.length() <= EPS) {
                // Total Internal Reflection
                Ray reflectRay(intersectionPoint + reflectDir * EPS, reflectDir);
                reflectCol = tracePath(reflectRay, depth - 1, scene);
            } else {
                // Only Refraction
                Ray refractRay(intersectionPoint + refractDir * EPS, refractDir);
                refractCol = tracePath(refractRay, depth - 1, scene);
            }

            R = reflectance(incident, -normal, eta, 1.0);
        }

        shade += R * reflectCol + (1 - R) * refractCol;
    }

    return mat.color * shade.clamp();
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
            int jitterGridSize = 1;
            for (int gridI = 0; gridI < jitterGridSize; ++gridI) {
                for (int gridJ = 0; gridJ < jitterGridSize; ++gridJ) {
                    Ray ray = camera->getRay(i, j, gridI, gridJ, jitterGridSize);
                    shade += tracePath(ray, 4, scene);
                }
            }
            camera->shadePixel(i, j, shade / (jitterGridSize * jitterGridSize));
        }
    }

    camera->saveFile("image");
}

vec3 SimpleRenderer::reflect(const vec3 &incident, const vec3 &normal) {
    return incident - 2.0 * vec3::dot(incident, normal) * normal;
}

vec3 SimpleRenderer::refract(const vec3 &incident, const vec3 &normal, double n1, double n2) {
    double n = n1 / n2;

    double cosI = -vec3::dot(incident, normal);
    double sin2T = n * n * (1.0 - cosI * cosI);

    // Total Internal Reflection
    if (sin2T > 1.0) {
        return vec3(0);
    }

    return n * incident + (n * cosI - sqrt(1 - sin2T)) * normal;
}

double SimpleRenderer::reflectance(const vec3 &incident, const vec3 &normal, double n1, double n2) {
    double R0 = pow((n1 - n2) / (n1 + n2), 2);

    double cosI = -vec3::dot(incident, normal);

    if (n1 > n2) {
        double n = n1 / n2;
        double sin2T = n * n * (1.0 - cosI * cosI);

        // Total Internal Reflection
        if (sin2T > 1.0) {
            return 1.0;
        }

        cosI = sqrt(1 - sin2T);
    }

    return R0 + (1 - R0) * pow(1.0 - cosI, 5);
}
