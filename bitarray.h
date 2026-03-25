// bitarray.h
// Řešení IJC-DU1, příklad a), 25.3.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)
// bitarray_t je pole unsigned long ke kteremu se chovame
// jako k poli bitu ve kterem pole[0] je velikost pole v bitech

#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "error.h"

typedef unsigned long bitarray_index_t;

typedef bitarray_index_t* bitarray_t;

// Number of bits in unsigned long
#define UL_BITS \
  (sizeof(bitarray_index_t)*__CHAR_BIT__)

// Initializes array of <size> bits
#define bitarray_create(name, size) \
  static_assert((size <= ~0UL) && (size > 0)); \
  bitarray_index_t name[((size)+2*UL_BITS-1)/UL_BITS] = {size, 0};

// Allocates array of <size> bits
#define bitarray_alloc(name, size) \
  assert((size <= 1UL<<(UL_BITS-1)) && size > 0); \
  bitarray_t name = \
  calloc(((size)+2*UL_BITS-1)/UL_BITS, sizeof(bitarray_index_t)); \
  if (!name) { \
    fprintf(stderr, "bitarray_alloc: Chyba alokace paměti"); \
    exit(EXIT_FAILURE);} \
  name[0] = size;


#ifndef USE_INLINE
// Frees allocated array
#define bitarray_free(name) \
  free(name);

// Returns size of array in bits
#define bitarray_size(name) \
  (name[0])

// Sets all bits in array to <value>
#define bitarray_fill(name, value) \
  memset(&name[1], ((value) ? 0xFF : 0), ((name[0]/8)+1))

// Create bitmask for given index, with respect to UL size
#define bit_mask(index) \
  (1UL << ((index) % UL_BITS))

// Sets bit on <index> to <value>
#define bitarray_setbit(name, index, value) \
  name[(index)/UL_BITS+1] = ( \
  check_range(name, index), \
  value ? \
  name[(index)/UL_BITS+1] | bit_mask(index) : \
  name[(index)/UL_BITS+1] & ~bit_mask(index));

// Get value of bit on <index>
#define bitarray_getbit(name, index) \
  (check_range((name), (index)),\
  (bit_mask(index) & name[index/UL_BITS+1]))


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

#ifndef NO_CHECK
  // Exits the program if given index is out of range (function)
  inline void check_range(bitarray_t arr, bitarray_index_t index) {
    if(index >= arr[0]) error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu\n", index, arr[0]);
  }
#else

  inline void check_range(bitarray_t arr, bitarray_index_t index) {
    (void)arr;
    (void)index;
  }
#endif

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
  for(unsigned int i = 1; i < (((arr[0])+2*UL_BITS-1)/UL_BITS); i++) \
    arr[i] = value ? ~0UL : 0UL;
}

// Create bitmask for given index, with respect to UL size (function)
inline bitarray_index_t bit_mask(bitarray_index_t index) {
  return 1UL << (index % UL_BITS);
}

// Sets bit on <index> to <value> (function)
inline void bitarray_setbit(bitarray_t arr, bitarray_index_t index, bool value) {
  check_range(arr, index);
  bitarray_index_t mask = bit_mask(index);
  if(value) \
    arr[(index / UL_BITS)+1] |=  mask;
  else \
    arr[(index / UL_BITS)+1] &= ~mask;
}

// Get value of bit on <index> (function)
inline bool bitarray_getbit(bitarray_t arr, bitarray_index_t index) {
  check_range(arr, index);
  return arr[(index/UL_BITS)+1] & bit_mask(index);
}

#endif
#endif