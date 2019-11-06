#include <camera/SimpleCamera.h>
#include <material/Dielectric.h>
#include <material/Glossy.h>
#include <material/Diffused.h>
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
            vec3 reflected = reflect(incident , normal);
            vec3 randReflect;
            double check;
            int k = 15; // Make k=0 for specular surface.
            do {
                vec3 randReflect = rndHemisphereDir(reflected);

                //debug("cos theta : %.5f" , vec3::dot(randReflect , reflected));
                check = vec3::dot(randReflect , normal);
            }while(check < 0.0  && !std::isnan(check)&& k-- > 0);
            if (k <=0)
                randReflect = reflected;
            Ray rndRay(isecPt + reflected*EPS , reflected);
            shade += tracePath(rndRay , depth-1  , scene);
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

    ull jg_size = 2;  // Jitter grid size
    ull n_samples = 10;  // Number of samples
    ull t_samples = n_samples * height * width * jg_size * jg_size;  // Total samples
    ull c_samples = 0;  // Completed samples

    fprintf(stderr, "\rProgress: %5.2Lf%%", ((long double)c_samples / t_samples) * 100);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Color pix_shade;
            for (int grid_i = 0; grid_i < jg_size; ++grid_i) {
                for (int grid_j = 0; grid_j < jg_size; ++grid_j) {
                	Color cur_shade;
                    for (int ns = 0; ns < n_samples; ++ns) {
                        Ray ray = camera->getRay(i, j, grid_i, grid_j, jg_size);
                        cur_shade += tracePath(ray, 8, scene);
                        ++c_samples;
                    }
                    pix_shade += cur_shade / n_samples;
                }
            }
    		fprintf(stderr, "\rProgress: %5.2Lf%%", ((long double)c_samples / t_samples) * 100);
            
            pix_shade /= jg_size * jg_size;
            pix_shade.clamp();
            camera->shadePixel(i, j, pix_shade);
        }
    }

    fprintf(stderr, "\n");
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

vec3 RealisticRenderer::glossyHemsiphereDir(const vec3 &reflect , const int m) {
    vec3 u, v, w;

    w = reflect;
    if (fabs(reflect.x) > EPS) {
        u = vec3(0, 0, 1);
    } else {
        u = vec3(1, 0, 0);
    }
    v = vec3::cross(w, u);

    double r1 = drand48();
    double r2 = drand48();

    long double cost = powf128(1-r1 , 1/(0.6+1));
    long double cos2t = powf128(1-r1 , 2/(0.6+1));
    long double phi = 2 * M_PI * r2;
    long double sint = sqrt(1-cos2t);
    long double cosp = cos(phi);
    long double sinp = sin(phi);

    vec3 localVec = ((cosp * sint * u) + (sinp * sint * v) + (cost * w)).normalize();

    return localVec;
}