#include "basicgeometricdist.h"
#include <math.h>
#include <string.h>
typedef struct pcg_state_setseq_64 { // Internals are *Private*.
  uint64_t state;                    // RNG state.  All values are possible.
  uint64_t inc;                      // Controls which RNG sequence (stream) is
                                     // selected. Must *always* be odd.
} pcg32_random_t;

static inline uint32_t pcg32_random_r(pcg32_random_t *rng) {
  uint64_t oldstate = rng->state;
  rng->state = oldstate * 6364136223846793005ULL + rng->inc;
  uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
  uint32_t rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

static inline uint32_t nextgeom(float p, pcg32_random_t *rng) {
  uint32_t rv = pcg32_random_r(rng);
  double frv = (double) rv / (UINT64_C(1)<<32); // return value in [0,1]
  return (uint32_t)(log(frv) / log(1.0 - p)); // obviously log(1.0-p) could be precomp.
}

bool fillwithrandombits(uint64_t * words, size_t size, float fraction, uint64_t seed) {
  memset(words, 0, size * sizeof(uint64_t));
  size_t maxval = size * 64;
  pcg32_random_t rng;
  rng.inc = 3;
  rng.state = seed;
  size_t t = nextgeom(fraction,&rng);
  while(t < maxval) {
    words[t / 64] |= (UINT64_C(1) << (t%64));
    t += nextgeom(fraction,&rng);
  }
  return true;

}
