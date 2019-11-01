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

    static inline double dot(const vec3 &a, const vec3 &b);
    static inline vec3 cross(const vec3 &a, const vec3 &b);

    inline vec3 &normalize();

    inline double length();

    inline vec3 operator*(vec3 vec) const;
    inline vec3 operator+(vec3 vec) const;
    inline vec3 operator-(vec3 vec) const;

    inline vec3 &operator*=(vec3 vec);
    inline vec3 &operator+=(vec3 vec);
    inline vec3 &operator-=(vec3 vec);

    inline vec3 operator*(double val) const;
    inline vec3 operator/(double val) const;
    inline vec3 &operator*=(double val);
    inline vec3 &operator/=(double val);

    inline friend vec3 operator*(double val, vec3 vec);

    inline friend vec3 operator-(vec3 vec);
    inline friend std::ostream &operator<<(std::ostream &out, vec3 vec);
};

vec3 &vec3::normalize() {
    double len = length();
    x /= len;
    y /= len;
    z /= len;

    return *this;
}

double vec3::length() {
    return std::sqrt(x * x + y * y + z * z);
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

vec3 &vec3::operator-=(const vec3 vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

vec3 vec3::operator*(const vec3 vec) const {
    return vec3(x * vec.x, y * vec.y, z * vec.z);
}

vec3 vec3::operator*(const double val) const {
    return vec3(x * val, y * val, z * val);
}

vec3 vec3::operator/(const double val) const {
    return vec3(x / val, y / val, z / val);
}

vec3 vec3::operator+(const vec3 vec) const {
    return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator-(const vec3 vec) const {
    return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 operator*(const double val, const vec3 vec) {
    return vec * val;
}

vec3 operator-(vec3 vec) {
    return vec * -1;
}

std::ostream &operator<<(std::ostream &out, const vec3 vec) {
    out << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return out;
}

#endif
