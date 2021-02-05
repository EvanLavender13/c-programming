#include <stdio.h>

int main(int argc, char **argv) {
    printf("Hello Y'all!\n");
	
	int a = 40;
	int *b = &a;
	printf("a is %d\n", a);
	printf("b is %x\n", b);
	printf("*b is %x\n", *b);

    return 0;
}
