
#include <x86intrin.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "util.h"
#include "simdxorshift128plus.h"
#include "simdrandombitstream.h"

#ifndef __AVX2__
#warning "You lack AVX2! This is not going to end well for you."
#endif


// utility function
static inline __m256i biasedvector_of_16bitmasks(__m256i mask_rev_p, avx_xorshift128plus_key_t * seed) {
  __m256i random = avx_xorshift128plus(seed);
  return _mm256_cmpeq_epi16( random, _mm256_max_epu16(mask_rev_p,random)) ;
}

// utility function
static inline __m256i biasedvector(__m256i mask_rev_p, avx_xorshift128plus_key_t * seed) {
  __m256i answer = _mm256_setzero_si256();
  __m256i mask = _mm256_set1_epi16(1);

  for(int k = 0; k < 16; k++) {
    __m256i v = biasedvector_of_16bitmasks(mask_rev_p,seed);
    v = _mm256_andnot_si256(v, mask);
    answer = _mm256_or_si256(answer, v);
    mask = _mm256_slli_epi16(mask,1);
  }
  return answer;
}

/**
* Write to the (possible uninitialized) buffer a given number of random words
* where the fraction of 1s is 'fraction' where 'fraction' is
* between 0 and 1. We use 16 bits of accuracy, so the fraction
* is theoretically accurate plus or minus 1/(1<<16) or 1.5e-05.
*
* You have to produce to 64-bit words as seeds, they should be non-zero.
* Given the same 64-bit seeds, you will get the same random bits each
* time.
*
* In practice, expect an accuracy of plus ou minus 0.0001 or 0.01 %.
*
*
* Return true when succesful. False if something is wrong with your
* parameters.
*
*/
bool avx_fillwithrandombits(__m256i * words, size_t size, float fraction, uint64_t seed1, uint64_t seed2) {
  if((fraction <= 0) || (fraction > 1)) {
    // fraction should be between 0 and 1
    return false;
  }
  if((seed1 & seed2) == 0) {
    // seeds should be non-zero
    return false;
  }
  avx_xorshift128plus_key_t seed;
  avx_xorshift128plus_init(seed1,seed2,&seed);
  int p = round(fraction * (1<<16));
  if(fraction == 1.0) p = (1<<16) - 1;
  __m256i mask_rev_p = _mm256_set1_epi16(p);//rev_p);
  for(size_t i = 0; i < size; i++) {
    __m256i  b = biasedvector(mask_rev_p,&seed);
    _mm256_storeu_si256(words + i, b);
  }
  return true;
}
