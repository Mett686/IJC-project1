#include <stdio.h>
#include "eratosthenes.c"
#include "bitarray.h"

int main(void) {
    bitarray_alloc(arr, 10000);
    Eratosthenes(arr);
    for(unsigned long i = 0; i < bitarray_size(arr); i++) {
        if(bitarray_getbit(arr, i)) printf("%lu\n", i);
    }
    bitarray_free(arr);
}