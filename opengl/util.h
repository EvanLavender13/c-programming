#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>

int
fsize(FILE *f)
{
    int sz;

    fseek(f, 0l, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    return sz;
}

#endif