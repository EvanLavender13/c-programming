#ifndef MEM_H_
#define MEM_H_

#include <stdlib.h>

static int refcount;

void *
memalloc(int n)
{
    refcount++;
    return malloc(n);
}

void
memfree(void *ptr)
{
    refcount--;
    free(ptr);
}

#endif