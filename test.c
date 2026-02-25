#include <stdio.h>
#include "bitarray.h"

int main(void) {
    printf("%ld\n",sizeof(unsigned long));
    bitarray_create(arr, 64);
    printf("%lx", arr[1]);
    bitarray_fill(arr, 1);
    printf("%lx", arr[1]);
}