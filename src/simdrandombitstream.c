
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <x86intrin.h>

#include "basicgeometricdist.h"
#include "simdrandombitstream.h"
#include "simdxorshift128plus.h"
#include "util.h"

#ifndef __AVX2__
#warning "You lack AVX2! This is not going to end well for you."
#endif

// we start with the least significant bits
/*static inline __m256i biasedvectorcircuit(bool * bits, size_t howmany,
avx_xorshift128plus_key_t * seed) { int i = 1;
  __m256i base;
  base = avx_xorshift128plus(seed);
  for(; i<howmany; i++) {
    __m256i x = avx_xorshift128plus(seed);
    if(bits[i]) {
        base =  _mm256_or_si256(x , ( _mm256_andnot_si256(x, base))) ;
    } else {
        base =  _mm256_and_si256(base, x );
    }
  }
  return base;
}*/

static inline __m256i biasedvectorcircuit1(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  return base;
}

static inline __m256i biasedvectorcircuit2(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit3(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit4(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  return base;
}

static inline __m256i biasedvectorcircuit5(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit6(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit7(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit8(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit9(bool *bits,
                                           avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit10(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit11(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[10]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit12(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[10]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[11]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit13(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[10]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[11]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[12]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit14(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[10]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[11]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[12]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[13]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

static inline __m256i biasedvectorcircuit15(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[10]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[11]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[12]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[13]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[14]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  return base;
}

static inline __m256i biasedvectorcircuit16(bool *bits,
                                            avx_xorshift128plus_key_t *seed) {
  __m256i base = _mm256_setzero_si256();
  __m256i x;
  x = avx_xorshift128plus(seed);
  if (bits[0]) {
    base = x;
  } else {
    //  base =  _mm256_and_si256(base, x );
  }
  x = avx_xorshift128plus(seed);

  if (bits[1]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[2]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[3]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[4]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[5]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[6]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[7]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[8]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[9]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[10]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[11]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[12]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[13]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[14]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }
  x = avx_xorshift128plus(seed);

  if (bits[15]) {
    base = _mm256_or_si256(x, (_mm256_andnot_si256(x, base)));
  } else {
    base = _mm256_and_si256(base, x);
  }

  return base;
}

bool avx_fillwithrandombits_circuit(__m256i *words, size_t size, float fraction,
                                    uint64_t seed1, uint64_t seed2) {
  if ((fraction <= 0) || (fraction > 1)) {
    // fraction should be between 0 and 1
    return false;
  }
  if ((seed1 & seed2) == 0) {
    // seeds should be non-zero
    return false;
  }
  avx_xorshift128plus_key_t seed;
  avx_xorshift128plus_init(seed1, seed2, &seed);
  int p = round(fraction * (1 << 16));
  bool bits[16];
  for (int b = 0; b < 16; b++) {
    bits[b] = p & (1 << b);
  }
  size_t offset = 0;
  while (!bits[offset])
    offset++;
  size_t howmany = 16 - offset;
  bool *abits = bits + offset;
  switch (howmany) {
  case 1:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit1(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 2:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit2(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 3:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit3(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 4:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit4(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 5:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit5(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 6:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit6(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 7:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit7(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 8:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit8(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 9:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit9(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 10:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit10(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 11:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit11(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 12:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit12(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 13:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit13(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 14:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit14(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 15:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit15(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  case 16:
    for (size_t i = 0; i < size; i++) {
      __m256i b = biasedvectorcircuit16(abits, &seed);
      _mm256_storeu_si256(words + i, b);
    }
    break;
  default:
    return false;
  }
  return true;
}

bool avx_fillwithrandombits_hybrid(__m256i *words, size_t size, float fraction,
                                   uint64_t seed1, uint64_t seed2) {
  if (fraction <= 0.007812) {
    return fillwithrandombits((uint64_t *)words, size * 4, fraction, seed1);
  } else {
    return avx_fillwithrandombits_circuit(words, size, fraction, seed1, seed2);
  }
}

// utility function
static inline __m256i
biasedvector_of_16bitmasks(__m256i mask_rev_p,
                           avx_xorshift128plus_key_t *seed) {
  __m256i random = avx_xorshift128plus(seed);
  return _mm256_cmpeq_epi16(random, _mm256_max_epu16(mask_rev_p, random));
}

// utility function
static inline __m256i biasedvector(__m256i mask_rev_p,
                                   avx_xorshift128plus_key_t *seed) {
  __m256i answer = _mm256_setzero_si256();
  __m256i mask = _mm256_set1_epi16(1);

  for (int k = 0; k < 16; k++) {
    __m256i v = biasedvector_of_16bitmasks(mask_rev_p, seed);
    v = _mm256_andnot_si256(v, mask);
    answer = _mm256_or_si256(answer, v);
    mask = _mm256_slli_epi16(mask, 1);
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
bool avx_fillwithrandombits(__m256i *words, size_t size, float fraction,
                            uint64_t seed1, uint64_t seed2) {
  if ((fraction <= 0) || (fraction > 1)) {
    // fraction should be between 0 and 1
    return false;
  }
  if ((seed1 & seed2) == 0) {
    // seeds should be non-zero
    return false;
  }
  avx_xorshift128plus_key_t seed;
  avx_xorshift128plus_init(seed1, seed2, &seed);
  int p = round(fraction * (1 << 16));
  if (fraction == 1.0)
    p = (1 << 16) - 1;
  __m256i mask_rev_p = _mm256_set1_epi16(p);
  for (size_t i = 0; i < size; i++) {
    __m256i b = biasedvector(mask_rev_p, &seed);
    _mm256_storeu_si256(words + i, b);
  }
  return true;
}
