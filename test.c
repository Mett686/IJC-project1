#include <stdio.h>
#include "eratosthenes.c"
#include "bitarray.h"

int main(void) {
    bitarray_create(arr, 100);
    Eratosthenes(arr);
    for(unsigned long i = 0; i < bitarray_size(arr); i++) {
        if(bitarray_getbit(arr, i)) printf("%lu\n", i);
    }
}
