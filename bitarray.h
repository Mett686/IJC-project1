// bitarray.h
// Řešení IJC-DU1, příklad a), 24.2.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)


#include <stdlib.h>

typedef unsigned long* bitarray_t;

typedef unsigned long bitarray_index_t;

#define ZERO_BITS 0x0000000000000000UL
#define ONE_BITS 0xffffffffffffffffUL

#define bitarray_create(name, size) \
    bitarray_index_t name[((size)+2*sizeof(bitarray_index_t)*__CHAR_BIT__-1)/(sizeof(bitarray_index_t)*__CHAR_BIT__)] = {size, 0}

#define bitarray_alloc(name, size) \
    bitarray_index_t name = calloc(((size)+2*sizeof(bitarray_index_t)*__CHAR_BIT__-1)/(sizeof(bitarray_index_t)*__CHAR_BIT__), sizeof(bitarray_index_t))

#define bitarray_free(name) \
    free(name)

#define bitarray_size(name) \
    name[0]

#define bitarray_fill(name, value) \
    for(unsigned long i = 1; i < name[0]; i++) name[i] = value ? ONE_BITS : ZERO_BITS

#define bitarray_setbit(name, index, value)
#define bitarray_getbit(name, index)
