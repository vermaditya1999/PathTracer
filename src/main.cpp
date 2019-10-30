#include <vector>

#include "Options.h"


int main(int argc , char *argv[])
{
    Options options(argc , argv);
    options.parse();

    std::vector<std::vector<int>> image;
    for(int i=0; i<256*256; i+=1){
        std::vector<int> v = {255 , 0 , 0};
        image.push_back(v);
    }
}