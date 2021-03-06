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

float
randfloat()
{
    return (float) random() / (float) RAND_MAX;
}

void
printarrf(float *arr, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("arr %f\n", *(arr + i));
    }
}

void
printarri(int *arr, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("arr %d\n", *(arr + i));
    }
}

#endif