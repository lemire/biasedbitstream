// Note: this is probably GARBAGE.

#include <stdint.h>
#include <stdio.h>
#include <x86intrin.h>

#include "util.h"
#include "simdxorshift128plus.h"

// tries to generate 16 bits where, at random
// bits are 1 or 0, and we want them to be
// 0 with probability p/(1<<16) where p is rev_p with the bit reversed, obviously p should
// be between 0 and (1<<16)-1. Or something.
uint16_t biasedword16(__m256i randomvector, __m256i mask_rev_p) {
  // in randomvector, we want to select just the least significant bit
  __m256i lowbits = _mm256_and_si256(randomvector,_mm256_sub_epi16(_mm256_setzero_si256(),randomvector));
  // formally: we should check whether a 2-byte word is zero, and patch things up
  // when it is the case. This occurs very rarely.
  __m256i bitstr = _mm256_cmpeq_epi16(_mm256_and_si256(mask_rev_p,lowbits),_mm256_setzero_si256());
  int intbitstr = _mm256_movemask_epi8(bitstr);
  return _pext_u32(intbitstr,0x55555555);
}

double demo(int p) {
  // create a new key
  avx_xorshift128plus_key_t mykey;
  avx_xorshift128plus_init(324,4444,&mykey); // values 324, 4444 are arbitrary, must be non-zero
  // generate 32 random bytes, do this as many times as you want
  int rev_p = bitreverse16(p);
  __m256i  mask_rev_p = _mm256_set1_epi16(rev_p);

  size_t total = 0;
  size_t total1s = 0;
  for(int k = 0; k < 1000000; k++) {
    total += 16;
    __m256i randomstuff =  avx_xorshift128plus(&mykey);
    total1s += __builtin_popcount(biasedword16(randomstuff,mask_rev_p));
  }
  return (double) (total - total1s) / (double) total;
}

int main() {
  // just checking that it makes sense
  for(int p = 5; p < 16; p++) {
    printf("p = %d (%f) ratio = %f \n", p,(double)(1<<p)/(1<<16), demo(1<<p));
  }
}
