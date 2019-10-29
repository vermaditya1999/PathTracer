#include <iostream>
#include <vector>
#include <cstdio>

void ppm_image(std::vector<std::vector<int>> &data , std::string file_name, int n , int m)
{
    FILE *fp = fopen(file_name.c_str() , "w");
    if (!fp){
        fprintf(stderr , "Cannot open file %s : " , file_name.c_str());
        perror(" ");
        return;
    }
    if (data.size() != n*m){
        std::cout << "Data not complete to print image" << std::endl;
        return;
    }

    fprintf(fp , "P3\n%d  %d\n255\n" , m , n);
    for(int i=0; i<n*m ;i+=1){
        fprintf(fp,"%d %d %d " , data[i][0] , data[i][1] , data[i][2]);
    }
}

int main()
{
    std::cout << "PathTracer" << std::endl;
    std::vector<std::vector<int>> image;
    for(int i=0; i<256*256; i+=1){
        std::vector<int> v = {255 , 0 , 0};
        image.push_back(v);
    }
    ppm_image(image , "file.ppm" , 256 , 256);
}