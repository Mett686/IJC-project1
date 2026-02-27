
#include <stdio.h>
#include "eratosthenes.h"
#include "bitarray.h"

#define N 444000000
#define P 10


int main(void) {
    bitarray_alloc(bitarray, N);
    Eratosthenes(bitarray);

    unsigned int i = (P) - 1;
    unsigned int j = (N) - 1;
    bitarray_index_t primes[P];
    while(i < P) {
        if(bitarray_getbit(bitarray, j)) {
            primes[i] = j;
            i--;
        }
        j--;
    }
    bitarray_free(bitarray);
    for(int i = 0; i < P; i++) {
        printf("%lu\n", primes[i]);
    }
    return EXIT_SUCCESS;
}