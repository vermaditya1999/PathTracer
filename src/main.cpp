#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "debug.h"


void ppm_image(std::vector<std::vector<int>> &data , std::string file_name, int n , int m)
{
    debug("Writing to file %s\n" , file_name.c_str());
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

class Options{
public:
    std::string filename;
    Options(int _argc , char *_argv[]): argc(_argc), argv(_argv)
    {}
    void parse();
private:
    int argc;
    char **argv;

};

#define usage() fprintf(stderr , "./PathTracer --file <filename>\n")

void Options::parse()
{
    if (argc==1){
        usage();
        exit(-1);
    }
    for(int  i=1 ; i<argc ; i++){
        if (!strcmp(argv[i] , "--file")){
            filename = argv[++i];
        }
        else{
            usage();
            exit(-1);
        }
    }
}

int main(int argc , char *argv[])
{

    Options options(argc , argv);
    options.parse();

    std::vector<std::vector<int>> image;
    for(int i=0; i<256*256; i+=1){
        std::vector<int> v = {255 , 0 , 0};
        image.push_back(v);
    }
    ppm_image(image , options.filename , 256 , 256);
}