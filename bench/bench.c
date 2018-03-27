#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "simdrandombitstream.h"
#include "benchmark.h"


int main() {
  printf("Running benchmarks...\n");
  const size_t size = 1024 * 1024 ;
  uint64_t * words = (uint64_t *)malloc(size * sizeof(uint64_t));
  int repeat = 5;
  bool verbose = true;
  for(double f = 0.00001; f <= 1; f *= 3.4) {
    printf("ratio %f, we display the number of cycles per 64-bit word generated \n", f);
    BEST_TIME_NOCHECK(avx_fillwithrandombits((__m256i *)words,size/4,f,rand(),rand()), , repeat, size,  verbose)  ;
  }
  printf("\n");
  return EXIT_SUCCESS;
}
