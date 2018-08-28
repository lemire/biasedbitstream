#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "simdrandombitstream.h"
#include "basicgeometricdist.h"

#include "benchmark.h"


int main() {
  printf("Running benchmarks...\n");
  const size_t size = 1024 * 1024 ;
  uint64_t * words = (uint64_t *)malloc(size * sizeof(uint64_t));
  int repeat = 5;
  bool verbose = true;
  for(int power = 1; power < 14; power ++) {
    float f = 1.0;
    for(int p = 0; p<power; p++) f *= 0.5;
    printf("\n\n\n ratio %f, we display the number of cycles per 64-bit word generated \n\n", f);
    BEST_TIME_NOCHECK(avx_fillwithrandombits_hybrid((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
    BEST_TIME_NOCHECK(avx_fillwithrandombits((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
    BEST_TIME_NOCHECK(avx_fillwithrandombits_circuit((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
    if(f < 0.25)  BEST_TIME_NOCHECK(fillwithrandombits((uint64_t *)words,size,f,rand()), , repeat, size,  verbose)  ;

  }
  for(float f = 0.5; f > 0.0001; f *= 0.34556) {
    printf("\n\n\n ratio %f, we display the number of cycles per 64-bit word generated \n\n", f);
    BEST_TIME_NOCHECK(avx_fillwithrandombits_hybrid((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
    BEST_TIME_NOCHECK(avx_fillwithrandombits((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
    BEST_TIME_NOCHECK(avx_fillwithrandombits_circuit((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
    if(f < 0.25)  BEST_TIME_NOCHECK(fillwithrandombits((uint64_t *)words,size,f,rand()), , repeat, size,  verbose)  ;

  }
  printf("\n");
  return EXIT_SUCCESS;
}
