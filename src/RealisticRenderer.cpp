#include <omp.h>
#include <camera/SimpleCamera.h>
#include <material/Dielectric.h>
#include <material/Glossy.h>
#include <material/SpecularDiffused.h>
#include "renderer/RealisticRenderer.h"

using ull = unsigned long long;

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
//            vec3 reflDir = reflect(incident, normal);  // Mirror
//            Ray reflRay(isecPt + reflDir * EPS, reflDir);
//            shade += tracePath(reflRay, depth - 1, scene);
            vec3 rndDir = rndReflHemisphereDir(normal, ((Glossy *) material)->alpha);
            Ray rndRay(isecPt + rndDir * EPS, rndDir);
            shade += tracePath(rndRay, depth - 1, scene);
        }
            break;
        case Material::Type::DIFFUSED: {
            vec3 rndDir = rndHemisphereDir(normal);
            Ray rndRay(isecPt + rndDir * EPS, rndDir);
            shade += tracePath(rndRay, depth - 1, scene);
        }
            break;
        case Material::Type::SPECULARDIFFUSED: {
            double prefl = ((SpecularDiffused*)material)->prefl;
            double R0 = prefl;
            double Rtheta = R0 + (1 - R0) * (1 - vec3::dot(incident, normal));  // specular reflectance

            double prob = drand48();
            if (prob < Rtheta) {
                // Choose reflections
                vec3 reflDir = reflect(incident, normal);
                Ray reflRay(isecPt + reflDir * EPS, reflDir);
                shade += Rtheta * tracePath(reflRay, depth - 1, scene);
            } else {
                // Choose diffused surface
                vec3 rndDir = rndHemisphereDir(normal);
                Ray rndRay(isecPt + rndDir * EPS, rndDir);
                shade += (1 - Rtheta) * tracePath(rndRay, depth - 1, scene);
            }
        } break;
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

    int jg_size = 2;  // Jitter grid size (n x n grid)
    int n_samples = 100;  // Number of samples
    int n_pixels = height * width;  // Number of pixels
    int r_pixels = 0;  // Number of rendered pixels

    fprintf(stdout, "\rProgress: %5.2f%%", 0.0);
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Color pix_shade;
            for (size_t grid_i = 0; grid_i < jg_size; ++grid_i) {
                for (size_t grid_j = 0; grid_j < jg_size; ++grid_j) {
                    Color cur_shade;
                    for (size_t ns = 0; ns < n_samples; ++ns) {
                        Ray ray = camera->getRay(i, j, grid_i, grid_j, jg_size);
                        cur_shade += tracePath(ray, 8, scene);
                    }
                    pix_shade += cur_shade / n_samples;
                }
            }
            pix_shade /= jg_size * jg_size;
            pix_shade.clamp();
            camera->shadePixel(i, j, pix_shade);
        }
#pragma omp critical
        r_pixels += width;
        fprintf(stdout, "\rProgress: %5.2f%%", (((double) r_pixels / n_pixels) * 100));
        fflush(stdout);
    }

    fprintf(stdout, "\n");
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
        u = vec3::cross(vec3(0, 0, 1), w).normalize();
    } else {
        u = vec3::cross(vec3(1, 0, 0), w).normalize();
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

vec3 RealisticRenderer::rndReflHemisphereDir(const vec3 &normal, double n) {
    // Create an axis (u, v, w) with w oriented along normal
    vec3 u, v, w;

    w = normal;
    if (fabs(normal.x) > EPS) {
        u = vec3::cross(vec3(0, 0, 1), w).normalize();
    } else {
        u = vec3::cross(vec3(1, 0, 0), w).normalize();
    }
    v = vec3::cross(w, u);

    // Create random unit vector in spherical coordinates
    // Reference: Realistic Ray Tracing
    double r1 = drand48();
    double r2 = drand48();

    double theta = acos(pow(1 - r1, 1 / (n + 1)));
    double phi = 2 * M_PI * r2;

    double cost = cos(theta);
    double sint = sin(theta);
    double cosp = cos(phi);
    double sinp = sin(phi);

    // Map the spherical coordinates to world axis
    vec3 localVec = ((cosp * sint * u) + (sinp * sint * v) + (cost * w)).normalize();

    return localVec;
}