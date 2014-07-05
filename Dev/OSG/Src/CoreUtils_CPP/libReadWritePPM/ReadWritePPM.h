#ifndef READ_WRITE_PPM_H
#define READ_WRITE_PPM_H

#include "Array.h"
#include "Color.h"

typedef Array<Color <int> > COLOR_ARRAY;
typedef Array<COLOR_ARRAY> COLOR_TBL;
typedef Array<COLOR_TBL> COLOR_VOL;

void read(COLOR_TBL & atblOut, const char * apchFileName);
void write(const char * apchFileName, const COLOR_TBL & atblIn);


#endif //READ_WRITE_PPM_H