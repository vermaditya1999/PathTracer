#include <iostream>
#include <vector>
#include <cstdio>



void ppm_image(std::vector<int> &data , std::string file_name, int n , int m)
{
    FILE *fp = fopen(file_name.c_str() , "w");
    if (!fp){
        fprintf(stderr , "Cannot open file %s : " , file_name.c_str());
        perror(" ");
        return;
    }
    if (data.size() != 3*n*m){
        std::cout << "Data not complete to print image" << std::endl;
        return;
    }

    std::fprintf(fp , "P3\n%d  %d\n255\n" , m , n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            fprintf(fp, "%c %c %c ", data[i*m+n], data[i*m+n+1], data[i*m+n+2]);
        }
    }
}

int main()
{
    std::cout << "PathTracer" << std::endl;
    std::vector<int> image;
    for(int i=0; i<256; i++){
        for(int j=0; j<256; j++){
            image.push_back(255);
            image.push_back(0);
            image.push_back(0);
        }
    }
    ppm_image(image , "file.ppm" , 256 , 256);
}