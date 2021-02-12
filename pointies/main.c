#include <stdio.h>

void
main(int argc, char *argv[])
{
    int a;
    int *b;
    int **c;

    a = 40;
    b = &a;
    c = &b;

    printf("Hello Y'all!\n");
    printf("a is %d\n", a);
    printf("b is %p\n", b);
    printf("*b is %d\n", *b);
    printf("c is %p\n", c);
    printf("**c is %d\n", **c);
}
