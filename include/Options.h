#ifndef PATHTRACER_OPTIONS_H
#define PATHTRACER_OPTIONS_H


#include <string>
#include <cstring>

#define usage() fprintf(stderr , "./PathTracer --file <filename>\n")

class Options {
private:
    int argc;
    char **argv;

public:
    std::string filename;

    Options(int _argc, char *_argv[]) : argc(_argc), argv(_argv) {}

    void parse();
};

void Options::parse() {
    if (argc == 1) {
        usage();
        exit(-1);
    }
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--file")) {
            filename = argv[++i];
        } else {
            usage();
            exit(-1);
        }
    }
}

#endif
