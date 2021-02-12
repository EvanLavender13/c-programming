# Pointies (Pointers)

int
```c
int a;
```

**pointer** to int
```c
int *b;
```

**pointer** to int **pointer**
```c
int **c;
```

`&` gives the address of a variable, so `b` is pointing to the address of `a`
```c
a = 40;
b = &a;
```

`*` gives the value that the pointer is pointing to, so `c` will be set to `40`
 ```c
 int c = *b;
 ```
