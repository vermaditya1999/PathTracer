#include "Triangle.h"

void Triangle::intersect(Ray &ray) {
    vec3 origin = ray.getOrigin();
    vec3 direction = ray.getDir();

    double a = p1.x - p2.x;
    double b = p1.y - p2.y;
    double c = p1.z - p2.z;
    double d = p1.x - p3.x;
    double e = p1.y - p3.y;
    double f = p1.z - p3.z;
    double g = direction.x;
    double h = direction.y;
    double i = direction.z;
    double j = p1.x - origin.x;
    double k = p1.y - origin.y;
    double l = p1.z - origin.z;

    double M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
    double beta = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
    double gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
    double t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;

    if (gamma < 0 || gamma > 1 || beta < 0 || beta > 1 - gamma)
        return;

    vec3 normal = vec3::cross(p3 - p2, p2 - p1).normalize();
    ray.setParam(this, normal, t);
}
