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

`&` gives the address of a variable, so `b` contains the address of `a`
```c
a = 40;
b = &a;
```

`*` gives the value at the address that the pointer contains, so `d` will be set to `40`
 ```c
 int d = *b;
 ```
