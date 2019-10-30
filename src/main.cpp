#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "debug.h"


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
}