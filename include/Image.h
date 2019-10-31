#ifndef PATHTRACER_IMAGE_H
#define PATHTRACER_IMAGE_H

#include <vector>
#include <iostream>

#include "vec3.h"
#include "Color.h"
#include "debug.h"

class Image {
private:
    int height, width;
    std::vector<Color> buffer;

public:
    explicit Image(int height, int width) : height(height), width(width), buffer(width * height) {}

    int getHeight() const;
    int getWidth() const;

    void setPixel(int row, int col, const Color color) {
        buffer[width * row + col] = color;
    }

    Color getPixel(int row, int col) const {
        return buffer[width * row + col];
    }

    void savePPM(std::string filename) const;
};

#endif
