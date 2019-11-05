#include <camera/SimpleCamera.h>
#include <material/Dielectric.h>
#include <material/Glossy.h>
#include <material/Diffused.h>
#include "renderer/RealisticRenderer.h"

/*
 * Check the intersection of ray with objects in the scene and
 * return the shade color.
 *
 * Effects: Reflection, Total Internal Reflection, Refraction,
 *          Dielectric Reflection and Refraction using Schlick's
 *          approximation for Fresnel's equations.
 * */
Color RealisticRenderer::tracePath(Ray &ray, int depth, Scene &scene) {
    if (depth <= 0) {
        return scene.getBackgroundColor();
    }

    auto &objects = scene.getObjects();
    for (auto &object: objects) {
        object->intersect(ray);
    }
    if (!ray.isect()) {
        return scene.getBackgroundColor();
    }

    vec3 normal = ray.getNormal();
    vec3 isecPt = ray.getIsectPt();
    vec3 incident = ray.getDir();

    const Material *material = ray.getIsectObj()->getMaterial();

    Color shade;
    switch (material->type) {
        case Material::Type::GLOSSY: {

        }
            break;
        case Material::Type::DIFFUSED: {
            vec3 rndDir = rndHemisphereDir(normal);
            Ray rndRay(isecPt + rndDir * EPS, rndDir);
            shade += tracePath(rndRay, depth - 1, scene);
        }
            break;
        case Material::Type::DIELECTRIC: {
            double eta = ((Dielectric *) material)->eta;
            double R;
            vec3 reflectDir, refractDir;
            Color reflectCol, refractCol;

            if (vec3::dot(incident, normal) < 0) {
                // Ray is going in the geometry
                reflectDir = reflect(incident, normal);
                refractDir = refract(incident, normal, 1.0, eta);

                Ray reflectRay(isecPt + reflectDir * EPS, reflectDir);
                Ray refractRay(isecPt + refractDir * EPS, refractDir);

                reflectCol = tracePath(reflectRay, depth - 1, scene);
                refractCol = tracePath(refractRay, depth - 1, scene);

                R = reflectance(incident, normal, 1.0, eta);
            } else {
                // Ray is going out from the geometry
                reflectDir = reflect(incident, -normal);
                refractDir = refract(incident, -normal, eta, 1.0);

                if (refractDir.length() <= EPS) {
                    // Total Internal Reflection
                    Ray reflectRay(isecPt + reflectDir * EPS, reflectDir);
                    reflectCol = tracePath(reflectRay, depth - 1, scene);
                } else {
                    // Only Refraction
                    Ray refractRay(isecPt + refractDir * EPS, refractDir);
                    refractCol = tracePath(refractRay, depth - 1, scene);
                }

                R = reflectance(incident, -normal, eta, 1.0);
            }

            shade += R * reflectCol + (1 - R) * refractCol;
        }
            break;
    }

    shade = material->emission + shade * material->color;

    return shade;
}

void RealisticRenderer::render(Scene scene) {
    Camera *camera = scene.getCamera();

    int height = camera->getImageHeight();
    int width = camera->getImageWidth();

    int jitterGridSize = 1;
    int numSamp = 1;
    double totSamp = numSamp * height * width * jitterGridSize;
    double compSamp = 0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Color shade;
            for (int gridI = 0; gridI < jitterGridSize; ++gridI) {
                for (int gridJ = 0; gridJ < jitterGridSize; ++gridJ) {
                    for (int ns = 0; ns < numSamp; ++ns) {
                        Ray ray = camera->getRay(i, j, gridI, gridJ, jitterGridSize);
                        shade += tracePath(ray, 8, scene);
                        ++compSamp;
                    }
                    shade /= numSamp;
                }
            }
            std::cout << "\rProgress: " << (compSamp / totSamp) * 100 << "%" << std::flush;
            camera->shadePixel(i, j, shade.clamp() / (jitterGridSize * jitterGridSize));
        }
    }

    camera->saveFile("image");
}

vec3 RealisticRenderer::reflect(const vec3 &incident, const vec3 &normal) {
    return incident - 2.0 * vec3::dot(incident, normal) * normal;
}

vec3 RealisticRenderer::refract(const vec3 &incident, const vec3 &normal, double n1, double n2) {
    double n = n1 / n2;

    double cosI = -vec3::dot(incident, normal);
    double sin2T = n * n * (1.0 - cosI * cosI);

    // Total Internal Reflection
    if (sin2T > 1.0) {
        return vec3(0);
    }

    return n * incident + (n * cosI - sqrt(1 - sin2T)) * normal;
}

double RealisticRenderer::reflectance(const vec3 &incident, const vec3 &normal, double n1, double n2) {
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

vec3 RealisticRenderer::rndHemisphereDir(const vec3 &normal) {
    // Create an axis (u, v, w) with w oriented along normal
    vec3 u, v, w;

    w = normal;
    if (fabs(normal.x) > EPS) {
        u = vec3(0, 0, 1);
    } else {
        u = vec3(1, 0, 0);
    }
    v = vec3::cross(w, u);

    // Create random unit vector in spherical coordinates
    // Reference: Realistic Ray Tracing
    double r1 = drand48();
    double r2 = drand48();

    double sint = sqrt(r1);
    double phi = 2 * M_PI * r2;

    double cost = sqrt(1 - r1);
    double cosp = cos(phi);
    double sinp = sin(phi);

    // Map the spherical coordinates to world axis
    vec3 localVec = ((cosp * sint * u) + (sinp * sint * v) + (cost * w)).normalize();

    return localVec;
}