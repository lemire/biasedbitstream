#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "simdrandombitstream.h"
#include "basicgeometricdist.h"


size_t countones(const uint64_t * words, size_t size) {
  size_t count = 0;
  for(size_t i = 0; i < size; i++)
    count +=__builtin_popcountll(words[i]);
  return count;
}

double computeratio(float fraction) {
  const size_t N = 1024 * 1024 * 2 ;
  uint64_t * words = (uint64_t *)malloc(N * sizeof(uint64_t));
  assert(avx_fillwithrandombits((__m256i *)words,N/4,fraction,rand(),rand()));
  size_t totalbits = N * 64;
  size_t onebits = countones(words,N);
  return (double) onebits / (double) totalbits;
}

double computeratio2(float fraction) {
  const size_t N = 1024 * 1024 * 2 ;
  uint64_t * words = (uint64_t *)malloc(N * sizeof(uint64_t));
  assert(avx_fillwithrandombits((__m256i *)words,N/4,fraction,rand(),rand()));
  size_t totalbits = N * 64;
  size_t onebits = countones(words,N);
  return (double) onebits / (double) totalbits;
}

double computeratiogeom(float fraction) {
  const size_t N = 1024 * 1024 * 2 ;
  uint64_t * words = (uint64_t *)malloc(N * sizeof(uint64_t));
  assert(fillwithrandombits((uint64_t *)words,N,fraction,rand()));
  size_t totalbits = N * 64;
  size_t onebits = countones(words,N);
  return (double) onebits / (double) totalbits;
}
bool geomtest() {
  printf("geometric distribution\n");
  float diff = 0;
  for(double f = 0.00001; f <= 0.25; f *= 1.1) {
    printf(".");
    fflush(NULL);
    float current = fabs(f-computeratiogeom(f));
    if(current > 0.0001) {
        printf("\n Error too high: %f \n", current);
        return false;
    }
    if(current > diff) diff = current;
  }
  printf("\n");
  printf("Code looks good, max error on 1s ratio = %f.\n", diff);
  return true;
}
bool avxtest2() {
  printf("vectorized2\n");
  float diff = 0;
  for(double f = 0.00001; f <= 1; f *= 1.1) {
    printf(".");
    fflush(NULL);
    float current = fabs(f-computeratio2(f));
    if(current > 0.0001) {
        printf("\n Error too high: %f \n", current);
        return false;
    }
    if(current > diff) diff = current;
  }
  printf("\n");
  printf("Code looks good, max error on 1s ratio = %f.\n", diff);
  return true;
}
bool avxtest() {
  printf("vectorized\n");
  float diff = 0;
  for(double f = 0.00001; f <= 1; f *= 1.1) {
    printf(".");
    fflush(NULL);
    float current = fabs(f-computeratio(f));
    if(current > 0.0001) {
        printf("\n Error too high: %f \n", current);
        return false;
    }
    if(current > diff) diff = current;
  }
  printf("\n");
  printf("Code looks good, max error on 1s ratio = %f.\n", diff);
  return true;
}

int main() {
  printf("Running tests...\n");
  if ( avxtest2() && geomtest() &&   avxtest()) return EXIT_SUCCESS;
  return EXIT_FAILURE;
}
