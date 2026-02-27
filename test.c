#include <stdio.h>
#include "eratosthenes.h"
#include "bitarray.h"

int main(void) {
    bitarray_alloc(arr, 444000000);
    Eratosthenes(arr);
    for(unsigned long i = 0; i < bitarray_size(arr); i++) {
        if(bitarray_getbit(arr, i)) printf("%lu\n", i);
    }
    bitarray_free(arr);
}