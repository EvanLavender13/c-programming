#ifndef MEM_H_
#define MEM_H_

static int refcount;

extern void *
memalloc(int n)
{
    refcount++;
    return MemAlloc(n);
}

extern void
memfree(void *ptr)
{
    refcount--;
    MemFree(ptr);
}

#endif