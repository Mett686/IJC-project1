// bitarray.h
// Řešení IJC-DU1, příklad a), 24.2.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>
#include "error.h"

typedef unsigned long* bitarray_t;

typedef unsigned long bitarray_index_t;


// Number of bits inside single element (unsigned long) inside bitarray
#define UL_BITS \
    (sizeof(bitarray_index_t)*__CHAR_BIT__)

// Initializes array of <size> bits
#define bitarray_create(name, size) \
    bitarray_index_t name[((size)+2*UL_BITS-1)/UL_BITS] = {size, 0}

// Allocates array of <size> bits
#define bitarray_alloc(name, size) \
    bitarray_t name = \
    calloc(((size)+2*UL_BITS-1)/UL_BITS, sizeof(bitarray_index_t)); \
    name[0] = size;

// Frees allocated array
#define bitarray_free(name) \
    free(name)

// Returns size of array in bits
#define bitarray_size(name) \
    name[0]

// Sets all bits in array to <value>
#define bitarray_fill(name, value) \
    for(bitarray_index_t i = 1; i < ((name[0])+2*UL_BITS-1)/UL_BITS; i++) \
    name[i] = value ? ~0UL : 0UL

// Create bitmask for given index, with respect to UL size
#define bit_mask(index) \
    (1UL << (UL_BITS - ((index) % UL_BITS) - 1))

// Sets bit on <index> to <value>
#define bitarray_setbit(name, index, value) \
    name[index/UL_BITS+1] = \
    value ? \
    name[index/UL_BITS+1] | bit_mask(index) : \
    name[index/UL_BITS+1] & ~bit_mask(index)

// Get value of bit on <index>
#define bitarray_getbit(name, index) \
    check_range(name, index) \
    (bit_mask(index) & name[index/UL_BITS+1]) == \
    bit_mask(index)

#ifndef NO_CHECK
#define check_range(name, index) \
    if(index > name[0]) \
    error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu", \
    (unsigned long)index, (unsigned long)name[0])
    
#else
#define check_range(name, index)
#endif

#endif