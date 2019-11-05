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

    shade.clamp();
    shade *= material->color;

    return shade;
}

void RealisticRenderer::render(Scene scene) {
    Camera *camera = scene.getCamera();

    int height = camera->getImageHeight();
    int width = camera->getImageWidth();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Color shade;
            int jitterGridSize = 4;
            for (int gridI = 0; gridI < jitterGridSize; ++gridI) {
                for (int gridJ = 0; gridJ < jitterGridSize; ++gridJ) {
                    Ray ray = camera->getRay(i, j, gridI, gridJ, jitterGridSize);
                    shade += tracePath(ray, 8, scene);
                }
            }
            camera->shadePixel(i, j, shade / (jitterGridSize * jitterGridSize));
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

vec3 rndHemiDir(const vec3 &normal) {
    // Create an axis (u, v, w) with v oriented along normal
    vec3 v = normal;
    vec3 u = vec3::cross(normal, vec3(normal.z, -normal.y, normal.x));
    vec3 w = vec3::cross(u, v);

    // Create random unit vector in spherical coordinates
    double theta = drand48() * M_PI_2;
    double phi = drand48() * M_PI;

    // Map the spherical coordinates to (u, v, w) axis
    // TODO: Make this efficient
    vec3 localVec(sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi));

    // Transform (u, v, w) to (x, y, z) axis
//    vec3 globalVec = localVec * ;

//    return globalVec;
}