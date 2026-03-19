// primes.c
// Řešení IJC-DU1, příklad a), 11.3.2026
// Autor: Martin Knotek, FIT
// Přeloženo: gcc version 15.2.1 20260123 (Red Hat 15.2.1-7) (GCC)

#include <stdio.h>
#include <time.h>
#include "eratosthenes.h"
#include "bitarray.h"

// Size of array
#define N 444000000
// Number of biggest primes to display
#define P 10

int main(void) {
  clock_t start = clock();

  bitarray_create(bitarray, N);
  Eratosthenes(bitarray);

  // Fill primes array with P number of biggest primes in ascending order
  bitarray_index_t primes[P];
  
  unsigned int i = 0;
  unsigned long j = (N) - 1;
  while(i < P) {
    if(bitarray_getbit(bitarray, j)) {
      primes[P-1-i] = j;
      i++;
    }
    j--;
  }

  for(unsigned int i = 0; i < P; i++) {
    printf("%lu\n", primes[i]);
  }
  
  fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}