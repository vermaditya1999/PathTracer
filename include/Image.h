#ifndef PATHTRACER_IMAGE_H
#define PATHTRACER_IMAGE_H

#include <vector>

#include "vec3.h"
#include "Color.h"

class Image {
    int height , width;
    std::vector<Color> buffer;
public:
    explicit Image(int height, int width) : height(height), width(width), buffer(width*height) {}

    int getHeight() const;

    int getWidth() const;

    void setPixel(int i, int j, const Color c){
        buffer[height*i + j] = c;
    }

    Color getPixel(int i, int j) const {
        return buffer[height*i + j];
    }

    void savePPM(std::string filename);
};


#endif //PATHTRACER_IMAGE_H
