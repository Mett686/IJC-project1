// bitarray.h
// Řešení IJC-DU1, příklad a), 26.2.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "error.h"

typedef unsigned long bitarray_index_t;

typedef bitarray_index_t* bitarray_t;

// Number of bits in unsigned long
#define UL_BITS \
    (sizeof(bitarray_index_t)*__CHAR_BIT__)

// Initializes array of <size> bits
#define bitarray_create(name, size) \
    ( (void)static_assert(size > 0,"bitarray_create: Chyba alokace paměti"), \
    bitarray_index_t name[((size)+2*UL_BITS-1)/UL_BITS] = {size, 0} )

// Allocates array of <size> bits
#define bitarray_alloc(name, size) \
    static_assert(size > 0,"bitarray_alloc: Chyba alokace paměti"); \
    bitarray_t name = \
    calloc(((size)+2*UL_BITS-1)/UL_BITS, sizeof(bitarray_index_t)); \
    name[0] = size;


#ifndef USE_INLINE
// Frees allocated array
#define bitarray_free(name) \
    free(name)

// Returns size of array in bits
#define bitarray_size(name) \
    name[0]

// Sets all bits in array to <value>
#define bitarray_fill(name, value) \
    for(unsigned int i = 1; i < ((name[0])+2*UL_BITS-1)/UL_BITS; i++) \
    name[i] = value ? ~0UL : 0UL

// Create bitmask for given index, with respect to UL size
#define bit_mask(index) \
    (1UL << (UL_BITS - ((index) % UL_BITS) - 1))

// Sets bit on <index> to <value>
#define bitarray_setbit(name, index, value) \
    check_range((name), (index)); \
    name[(index)/UL_BITS+1] = \
    value ? \
    name[(index)/UL_BITS+1] | bit_mask(index) : \
    name[(index)/UL_BITS+1] & ~bit_mask(index)

// Get value of bit on <index>
#define bitarray_getbit(name, index) \
    (check_range((name), (index)), bit_mask(index)) == \
    (bit_mask(index) & name[index/UL_BITS+1])
    

#ifndef NO_CHECK
    // Exits the program if given index is out of range
    #define check_range(name, index) \
        ( ((index) >= (name)[0]) ? \
        (error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu", \
        (bitarray_index_t)(index), (bitarray_index_t)(name)[0]), (void)0) \
        : (void)0 )

#else
    // check_range disabled
    #define check_range(name, index) \
        ((void)0)
#endif
#endif

#ifdef USE_INLINE

// Frees allocated array (function)
inline void bitarray_free(bitarray_t arr) {
    free(arr);
}

// Returns size of array in bits (function)
inline bitarray_index_t bitarray_size(bitarray_t arr) {
    return arr[0];
}

// Sets all bits in array to <value> (function)
inline void bitarray_fill(bitarray_t arr, bool value) {
    bitarray_index_t num = value ? ~0UL : 0UL;
    for(unsigned int i = 1; i < ((arr[0])+UL_BITS-1)/UL_BITS; i++) {
        arr[i] = num;
    }
}

// Create bitmask for given index, with respect to UL size (function)
inline bitarray_index_t bit_mask(bitarray_index_t index) {
    return 1UL << (UL_BITS - (index % UL_BITS) - 1);
}

// Sets bit on <index> to <value> (function)
inline void bitarray_setbit(bitarray_t arr, bitarray_index_t index, bool value) {
    check_range(arr, index);
    bitarray_index_t num = arr[index/UL_BITS+1];
    bitarray_index_t mask = bit_mask(index);
    arr[index / UL_BITS+1] = value ? num | mask : num & ~mask;
}

// Get value of bit on <index> (function)
inline bool bitarray_getbit(bitarray_t arr, bitarray_index_t index) {
    check_range(arr, index);
    bitarray_index_t num = arr[index/UL_BITS+1];
    bitarray_index_t mask = bit_mask(index);
    return mask & num == mask;
}

#ifndef NO_CHECK
    // Exits the program if given index is out of range (function)
    inline void check_range(bitarray_t arr, bitarray_index_t index) {
        if(index >= arr[0]) {
            char *fmt = "bitarray_getbit: Index %lu mimo rozsah 0..%lu";
            error_exit(fmt, index, arr[0]);
        }
    }
#else

    inline void check_range(bitarray_t arr, bitarray_index_t index);
#endif
#endif
#endif