#ifndef PATHTRACER_COLOR_H
#define PATHTRACER_COLOR_H


#include <ostream>


class Color {
public:
    double r, g, b;

    explicit Color() : r(0.0), g(0.0), b(0.0) {}

    explicit Color(double value) : r(value), g(value), b(value) {}

    explicit Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}

    inline void clamp();

    inline Color operator*(Color color);

    inline Color operator*(double val);

    inline Color operator/(Color color);

    inline Color operator/(double val);

    inline Color operator+(Color color);

    inline Color operator+(double val);

    inline Color operator-(Color color);

    inline Color operator-(double val);

    inline Color &operator*=(Color color);

    inline Color &operator*=(double val);

    inline Color &operator/=(Color color);

    inline Color &operator/=(double val);

    inline Color &operator+=(Color color);

    inline Color &operator+=(double val);

    inline Color &operator-=(Color color);

    inline Color &operator-=(double val);

    inline friend std::ostream &operator<<(std::ostream &out, Color color);
};

void Color::clamp() {
    if (r < 0) r = 0.0;
    if (g < 0) g = 0.0;
    if (b < 0) b = 0.0;
    if (r > 1) r = 1.0;
    if (g > 1) g = 1.0;
    if (b > 1) b = 1.0;
}

Color &Color::operator*=(const Color color) {
    r *= color.r;
    g *= color.g;
    b *= color.b;

    return *this;
}

Color &Color::operator*=(const double val) {
    r *= val;
    g *= val;
    b *= val;

    return *this;
}

Color &Color::operator/=(const Color color) {
    r /= color.r;
    g /= color.g;
    b /= color.b;

    return *this;
}

Color &Color::operator/=(const double val) {
    r /= val;
    g /= val;
    b /= val;

    return *this;
}

Color &Color::operator+=(const Color color) {
    r += color.r;
    g += color.g;
    b += color.b;

    return *this;
}

Color &Color::operator+=(const double val) {
    r += val;
    g += val;
    b += val;

    return *this;
}

Color &Color::operator-=(const Color color) {
    r -= color.r;
    g -= color.g;
    b -= color.b;

    return *this;
}

Color &Color::operator-=(const double val) {
    r -= val;
    g -= val;
    b -= val;

    return *this;
}

Color Color::operator*(const Color color) {
    return Color(r * color.r, g * color.g, b * color.b);
}

Color Color::operator*(const double val) {
    return Color(r * val, g * val, b * val);
}

Color Color::operator/(const Color color) {
    return Color(r / color.r, g / color.g, b / color.b);
}

Color Color::operator/(const double val) {
    return Color(r / val, g / val, b / val);
}

Color Color::operator+(const Color color) {
    return Color(r + color.r, g + color.g, b + color.b);
}

Color Color::operator+(const double val) {
    return Color(r + val, g + val, b + val);
}

Color Color::operator-(const Color color) {
    return Color(r - color.r, g - color.g, b - color.b);
}

Color Color::operator-(const double val) {
    return Color(r - val, g - val, b - val);
}

std::ostream &operator<<(std::ostream &out, const Color color) {
    out << "[" << color.r << ", " << color.g << ", " << color.b << "]";
    return out;
}


#endif
