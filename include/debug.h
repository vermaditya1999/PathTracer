#ifndef PATHTRACER_DEBUG_H
#define PATHTRACER_DEBUG_H

#include <cstdio>

#ifdef DEBUG
#define debug(fmt , ...) do {\
    fprintf(stderr , "[%s:%s():%d] ", __FILE__ , __func__ , __LINE__  );\
    fprintf(stderr , fmt , __VA_ARGS__); \
    fputs("\n", stderr); \
} while(0)
#else
#define debug(fmt , ...)
#endif

#endif
