#ifndef DSF2DSDIFF_H
#define DSF2DSDIFF_H
#include <stdlib.h>
#define ASSERT(COND, MSG) if(!(COND)) {\
    fputs(MSG, stderr);\
    fputs("\n", stderr);\
    exit(EXIT_FAILURE);\
    }

#endif