#include <stdlib.h>
#include "bitarray.h"

void bitarray_free(bitarray_t arr) {
    free(arr);
}

bitarray_index_t bitarray_getsize(bitarray_t arr) {
    return arr[0];
}

void bitarray_fill(bitarray_t arr, bool value) {
    for(bitarray_index_t i = 1; i < ((name[0])+2*UL_BITS-1)/UL_BITS; i++) {
    name[i] = value ? ~0UL : 0UL;
    }
}

void bitarray_setbit(bitarray_t arr, bitarray_index_t index, bool value) {
    bita
    arr[(index)/UL_BITS+1] = value ?
    arr[(index)/UL_BITS+1] | bit_mask(index) : arr[index/UL_BITS+1] & ~bit_mask(index);
}