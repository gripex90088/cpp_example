#include <stdio.h>

#define zend_long long

typedef int custom_int;


typedef union _zend_value {
    zend_long lval;
} zend_value;

typedef struct _zend_array zend_array;

typedef struct _zend_array HashTable;

struct _zend_array {

};

#define enint int

struct _zavl_struct {
    zend_value value;
    union u1;
    union u2;
};

int main()
{
    printf("Hello world\n");
    return 0;
}

