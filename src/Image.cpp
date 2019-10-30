#include <cstdio>
#include <iostream>

#include "Image.h"
#include "debug.h"


int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

void Image::savePPM(std::string filename) {
    debug("Writing to file %s\n", filename.c_str());
    FILE *fp = fopen(filename.c_str(), "w");
    if (!fp) {
        fprintf(stderr, "Cannot open file %s : ", filename.c_str());
        perror(" ");
        return;
    }
    if (buffer.size() != height*width) {
        std::cout << "Data not complete to print Image" << std::endl;
        return;
    }

    fprintf(fp, "P3\n%d  %d\n255\n", height, width );
    for (int i = 0; i < height * width ; ++i) {
        fprintf(fp, "%d %d %d ", (int)buffer[i].r*255, (int)buffer[i].g*255, (int)buffer[i].b*255);
    }
}