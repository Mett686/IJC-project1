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

// Mask for reading single bits ( 0b100...00 )
#define BIT_MASK 0x8000000000000000UL

// Number of bits inside single element inside bitarray
#define UL_BITS (sizeof(bitarray_index_t)*__CHAR_BIT__)

// 
#define bitarray_create(name, size) \
    bitarray_index_t name[((size)+2*UL_BITS-1)/UL_BITS] = {size, 0}

#define bitarray_alloc(name, size) \
    bitarray_index_t name = \
    calloc(((size)+2*UL_BITS-1)/UL_BITS, sizeof(bitarray_index_t))

#define bitarray_free(name) \
    free(name)

#define bitarray_size(name) \
    name[0]

#define bitarray_fill(name, value) \
    for(bitarray_index_t i = 1; i < ((name[0])+2*UL_BITS-1)/UL_BITS; i++) \
    name[i] = value ? ~0UL : 0UL

#define bitarray_setbit(name, index, value) \
    name[index/UL_BITS+1] = \
    value ? \
    name[index/UL_BITS+1] | (BIT_MASK >> ((index) % UL_BITS)) : \
    name[index/UL_BITS+1] & ~(BIT_MASK >> ((index) % UL_BITS))

#define bitarray_getbit(name, index) \
    ((BIT_MASK >> ((index) % UL_BITS)) & name[index/UL_BITS+1]) == \
    (BIT_MASK >> ((index) % UL_BITS))

#endif