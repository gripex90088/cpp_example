```cpp

static library 

g++ -c -o file.o file.c  
ar cr libfile.a file.o
g++ -std=c++11 main.cpp -lfile -L.

```


```cpp

share library

g++ -c -fPIC file.c -o hello.o
g++ -shared hello.o -o libhello.so 
```
