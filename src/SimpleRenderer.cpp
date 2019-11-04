#include "SimpleRenderer.h"

/*
 * Check the intersection of ray with objects in the scene and
 * return the shade color.
 * */
Color SimpleRenderer::tracePath(Ray &ray, int depth, Scene &scene) {
    Camera *camera = scene.getCamera();
    auto &lights = scene.getLights();
    auto &objects = scene.getObjects();

    vec3 normal = ray.getNormal();
    vec3 intersectionPoint = ray.getIntersectedPoint();
    vec3 incident = ray.getDirection();
    vec3 viewDirection = (camera->getPosition() - intersectionPoint).normalize();

    Material mat = ray.getIntersectedObject()->getMaterial();
    double ka = mat.ka;
    double kd = mat.kd;
    double ks = mat.ks;
    double alpha = mat.alpha;
    bool dielectric = mat.dielectric;
    double eta = mat.eta;

    Color finalColor;

    if (!dielectric) {
        for (auto light : lights) {
            vec3 lightDirection = (light->getPosition() - intersectionPoint).normalize();
            vec3 reflectedDirection = (2 * vec3::dot(lightDirection, normal) * normal - lightDirection).normalize();

            // Check for shadows
            Ray shadowFeeler(intersectionPoint + lightDirection * EPS, lightDirection);
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
                        ks * light->getColor() *
                        std::max(pow(vec3::dot(reflectedDirection, viewDirection), alpha), 0.0);
            }
        }

        finalColor += Color(ka);
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

            for (auto object : objects) {
                object->intersect(reflectRay);
                object->intersect(refractRay);
            }

            if (reflectRay.intersected()) {
                reflectCol = tracePath(reflectRay, depth - 1, scene);
            }

            if (refractRay.intersected()) {
                refractCol = tracePath(refractRay, depth - 1, scene);
            }

            R = reflectance(incident, normal, 1.0, eta);
        } else {
            // Ray is going out from the object
            reflectDir = reflect(incident, -normal);
            refractDir = refract(incident, -normal, eta, 1.0);

            if (refractDir.length() <= EPS) {
                // Total Internal Reflection
                Ray reflectRay(intersectionPoint + reflectDir * EPS, reflectDir);

                for (auto object : objects) {
                    object->intersect(reflectRay);
                }

                if (reflectRay.intersected()) {
                    reflectCol = tracePath(reflectRay, depth - 1, scene);
                }
            } else {
                Ray refractRay(intersectionPoint + refractDir * EPS, refractDir);

                for (auto object : objects) {
                    object->intersect(refractRay);
                }

                if (refractRay.intersected()) {
                    refractCol = tracePath(refractRay, depth - 1, scene);
                }
            }

            R = reflectance(incident, -normal, eta, 1.0);
        }

        finalColor += R * reflectCol + (1 - R) * refractCol;
    }

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
            int jitterGridSize = 8;
            for (int gridI = 0; gridI < jitterGridSize; ++gridI) {
                for (int gridJ = 0; gridJ < jitterGridSize; ++gridJ) {
                    Ray ray = camera->getRay(i, j, gridI, gridJ, jitterGridSize);
                    for (auto object : objects) {
                        object->intersect(ray);
                    }
                    if (ray.intersected()) {
                        shade += tracePath(ray, 4, scene);
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
