#ifndef PATHTRACER_VEC3_H
#define PATHTRACER_VEC3_H


#include <cmath>
#include <ostream>


class vec3 {
public:
    double x, y, z;

    explicit vec3() : x(0.0), y(0.0), z(0.0) {}

    explicit vec3(double value) : x(value), y(value), z(value) {}

    explicit vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    static inline vec3 &normalize(vec3 &vec);

    static inline double length(const vec3 &vec);

    static inline double dot(const vec3 &a, const vec3 &b);

    static inline vec3 cross(const vec3 &a, const vec3 &b);

    inline vec3 operator*(vec3 vec);

    inline vec3 operator*(double val);

    inline vec3 operator/(vec3 vec);

    inline vec3 operator/(double val);

    inline vec3 operator+(vec3 vec);

    inline vec3 operator+(double val);

    inline vec3 operator-(vec3 vec);

    inline vec3 operator-(double val);

    inline vec3 &operator*=(vec3 vec);

    inline vec3 &operator*=(double val);

    inline vec3 &operator/=(vec3 vec);

    inline vec3 &operator/=(double val);

    inline vec3 &operator+=(vec3 vec);

    inline vec3 &operator+=(double val);

    inline vec3 &operator-=(vec3 vec);

    inline vec3 &operator-=(double val);

    inline friend std::ostream &operator<<(std::ostream &out, vec3 vec);
};

vec3 &vec3::normalize(vec3 &vec) {
    double len = vec3::length(vec);
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;

    return vec;
}

double vec3::length(const vec3 &vec) {
    std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double vec3::dot(const vec3 &a, const vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3::cross(const vec3 &a, const vec3 &b) {
    return vec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

vec3 &vec3::operator*=(const vec3 vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;

    return *this;
}

vec3 &vec3::operator*=(const double val) {
    x *= val;
    y *= val;
    z *= val;

    return *this;
}

vec3 &vec3::operator/=(const vec3 vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;

    return *this;
}

vec3 &vec3::operator/=(const double val) {
    x /= val;
    y /= val;
    z /= val;

    return *this;
}

vec3 &vec3::operator+=(const vec3 vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

vec3 &vec3::operator+=(const double val) {
    x += val;
    y += val;
    z += val;

    return *this;
}

vec3 &vec3::operator-=(const vec3 vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

vec3 &vec3::operator-=(const double val) {
    x -= val;
    y -= val;
    z -= val;

    return *this;
}

vec3 vec3::operator*(const vec3 vec) {
    return vec3(x * vec.x, y * vec.y, z * vec.z);
}

vec3 vec3::operator*(const double val) {
    return vec3(x * val, y * val, z * val);
}

vec3 vec3::operator/(const vec3 vec) {
    return vec3(x / vec.x, y / vec.y, z / vec.z);
}

vec3 vec3::operator/(const double val) {
    return vec3(x / val, y / val, z / val);
}

vec3 vec3::operator+(const vec3 vec) {
    return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator+(const double val) {
    return vec3(x + val, y + val, z + val);
}

vec3 vec3::operator-(const vec3 vec) {
    return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 vec3::operator-(const double val) {
    return vec3(x - val, y - val, z - val);
}

std::ostream &operator<<(std::ostream &out, const vec3 vec) {
    out << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return out;
}


#endif
