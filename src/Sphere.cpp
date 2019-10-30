
#include <cmath>

#include "Sphere.h"
#include "vec3.h"
#include "debug.h"


void Sphere::intersect(Ray &ray) {
    debug("Checking Ray intersection with sphere %d" , 1);

    vec3 origin = ray.getOrigin() , dir = ray.getDirection();
    vec3 cv = origin - center;
    double a = 1.0;
    double b = 2*dir.dot(cv);
    double c = cv.dot(cv) - radius*radius;
    double D = b*b - 4*a*c;

    if (D == 0.0) {
        double t = -b/(2*a);
        ray.setParameter(this , t);
    }

    if (D > 0.0){
        double d = sqrt(D);
        double t1 = (-b + d)/(2*a) , t2 = (-b - d)/(2*a);
        ray.setParameter(this , t1);
        ray.setParameter(this , t2);
    }
}