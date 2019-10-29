#ifndef PATHTRACER_DEBUG_H
#define PATHTRACER_DEBUG_H


#include <cstdio>

#ifndef NDEBUG
#define debug(fmt , ...) do {\
    fprintf(stderr , "[%s:%s():%d] ", __FILE__ , __FUNC__ , __LINE__  );\
    fprintf(stderr , fmt , __VA_ARGS__); \
    puts(""); \
}while(0)
#else
#define debug(fmt , ...)
#endif

#endif
