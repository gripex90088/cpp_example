#include <stdio.h>

int main()
{
    int i, j;
    printf("Hello world\n");

    
    for (i = 0; i < 100; i++) {
        printf("current i is %d\n", i);
        for (j = 0; j < 100; j++) {
            printf("current j is %d\n", i);
        }
    }

    return 0;
}

