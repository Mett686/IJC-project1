// bitarray.c
// Řešení IJC-DU1, příklad a), 25.3.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#ifdef USE_INLINE
#include "bitarray.h"

// Frees allocated array (function)
extern inline void bitarray_free(bitarray_t arr);

// Returns size of array in bits (function)
extern inline bitarray_index_t bitarray_size(bitarray_t arr);

// Sets all bits in array to <value> (function)
extern inline void bitarray_fill(bitarray_t arr, bool value);

// Create bitmask for given index, with respect to UL size (function)
extern inline bitarray_index_t bit_mask(bitarray_index_t index);

// Sets bit on <index> to <value> (function)
extern inline void bitarray_setbit(bitarray_t arr, bitarray_index_t index, bool value);

// Get value of bit on <index> (function)
extern inline bool bitarray_getbit(bitarray_t arr, bitarray_index_t index);

// Exits the program if given index is out of range (function)
extern inline void check_range(bitarray_t arr, bitarray_index_t index);

#endif