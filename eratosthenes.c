#include <stdlib.h>
#include <math.h>
#include "bitarray.h"

void Eratosthenes(bitarray_t arr) {
    bitarray_fill(arr, 1);
    bitarray_setbit(arr, 0, 0);
    bitarray_setbit(arr, 1, 0);
    
    unsigned long N = bitarray_size(arr);
    unsigned long threshold = sqrt(N);
    unsigned long i = 2;
    while(i < threshold) {
        if(bitarray_getbit(arr, i)) {
            unsigned long j = i+i;
            while(j < N) {
                bitarray_setbit(arr, j, 0);
                j += i;
            }
        }
        i++;
    }
}