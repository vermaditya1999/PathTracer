#include <cmath>

#include "Sphere.h"
#include "vec3.h"

void Sphere::intersect(Ray &ray) {
    vec3 origin = ray.getOrigin(), dir = ray.getDir();
    vec3 cv = origin - center;
    double a = 1.0;
    double b = 2 * vec3::dot(dir, cv);
    double c = vec3::dot(cv, cv) - radius * radius;
    double D = b*b - 4*a*c;

    if (D == 0.0) {
        double t = -b/(2*a);
        ray.setParam(this, (origin + dir * t - center).normalize(), t);
    }

    if (D > 0.0) {
        double d = sqrt(D);
        double t1 = (-b + d) / (2 * a), t2 = (-b - d) / (2 * a);
        ray.setParam(this, (origin + dir * t1 - center).normalize(), t1);
        ray.setParam(this, (origin + dir * t2 - center).normalize(), t2);
    }
}