#include <cstdio>
#include <iostream>

#include "Image.h"

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

void Image::savePPM(std::string filename) const {

    FILE *filePointer = fopen(filename.c_str(), "w");
    if (!filePointer) {
        fprintf(stderr, "Cannot open file %s : ", filename.c_str());
        perror(" ");
        return;
    }

    fprintf(filePointer, "P3\n%d  %d\n255\n", width, height);
    for (int i = 0; i < height * width ; ++i) {
        fprintf(filePointer, "%d %d %d ", (int) (buffer[i].r * 255),
                (int) (buffer[i].g * 255),
                (int) (buffer[i].b * 255));
    }
}