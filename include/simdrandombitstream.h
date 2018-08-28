#ifndef SIMDRANDOMBITSTREAM_H
#define SIMDRANDOMBITSTREAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <x86intrin.h>

#ifdef __AVX2__

/**
 * Write to the (possibly uninitialized) buffer a given number of random words
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

bool avx_fillwithrandombits_hybrid(__m256i *words, size_t size, float fraction,
                                   uint64_t seed1, uint64_t seed2);

bool avx_fillwithrandombits(__m256i *words, size_t size, float fraction,
                            uint64_t seed1, uint64_t seed2);

bool avx_fillwithrandombits_circuit(__m256i *words, size_t size, float fraction,
                                    uint64_t seed1, uint64_t seed2);

#else
#warning "You need AVX2!"

#endif
#endif
