#ifndef BASICGEOMETRICDIST_H
#define BASICGEOMETRICDIST_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>




/**
* Write to the (possible uninitialized) buffer a given number of random words
* where the fraction of 1s is 'fraction' where 'fraction' is
* between 0 and 1. We use 16 bits of accuracy, so the fraction
* is theoretically accurate plus or minus 1/(1<<16) or 1.5e-05.
*
* Return true when succesful. False if something is wrong with your
* parameters.
*
*/
bool fillwithrandombits(uint64_t * words, size_t size, float fraction, uint64_t seed);


#endif
