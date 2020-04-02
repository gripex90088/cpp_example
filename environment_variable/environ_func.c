#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *val;
    const char *name = "ABC";
    
    val = getenv(name);
    printf("1, %s = %s\n", name, val);

    setenv(name, "haha-day-and-night", 1);
    
    val = getenv(name);
    printf("2, %s = %s\n", name, val);
    
#if 0
    int ret = unsetenv("ABCGDG");
    printf("ret = %d\n", ret);

    val = getenv(name);
    printf("3, %s = %s\n", name, val);

#else
    int ret = unsetenv("ABD");
    printf("ret = %d\n", ret);

    val = getenv(name);
    printf("3, %s = %s\n", name, val);

#endif

    return 0;
}

