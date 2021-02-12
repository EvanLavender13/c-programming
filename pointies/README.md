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

`&` gives the address of a variable, so `b` is contains the address of `a`
```c
a = 40;
b = &a;
```

`*` gives the value of the address that the point contains, so `d` will be set to `40`
 ```c
 int d = *b;
 ```
