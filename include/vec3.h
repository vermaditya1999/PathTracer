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

    inline void normalize();

    inline double length() const;

    inline double dot(vec3 vec) const;

    inline vec3 cross(vec3 vec) const;

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

    friend std::ostream &operator<<(std::ostream &out, vec3 vec);
};

double vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

void vec3::normalize() {
    double len = length();
    x /= len;
    y /= len;
    z /= len;
}

double vec3::dot(const vec3 vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

vec3 vec3::cross(const vec3 vec) const {
    return vec3(y * vec.z - z * vec.y,
                z * vec.x - x * vec.z,
                x * vec.y - y * vec.x);
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
