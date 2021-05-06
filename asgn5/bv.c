#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct  BitVector {
    uint32_t  length; //  Length  in bits.
    uint8_t *vector; // Array of bytes.
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = calloc(1 , sizeof(BitVector)); // 1 refers to 1 byte
    if (!bv) { // error if bv allocated incorrectly
        return NULL;
    }
    bv->length = length;
    bv->vector = calloc((length / 8 + length % 8), sizeof(uint8_t)); // length is in bits, need to convert to bytes
    // initialize each bit in bit vector to 0
    for (int i = 0; i < length; i++) {
        bv->vector[i] = 0;
    }
    if (!bv->vector) { // error if bv allocated incorrectly
        return NULL;
    }
    return bv;
}

// frees memory allocated for BitVector
void bv_delete(BitVector **v) {
    // TODO: fix err
    //free((&v)->vector);
    free(*v);
    *v = NULL;
}

// returns the length in bits of the BitVector
uint32_t bv_length(BitVector *v) {
    return v->length;
}

// sets the bit at index in the BitVector
// i = index of bit to set
void bv_set_bit(BitVector *v, uint32_t i) {
    //set bit at i to 1
    v->vector[i/8] |= (0x1 << (i % 8)); // || og byte with 00..1..00
}

// clears the bit at index in the BitVector
// i = index of the bit to clear
void bv_clr_bit(BitVector *v, uint32_t i) {
    // set bit at i to 0
    v->vector[i / 8] &= ~(0x1 << (i % 8)); // && og byte with 11..0..11
}

// xors the i-th bit in v with value of specified bit
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
   v->vector[i / 8] ^= (bit << (i % 8)); //TODO: check
}
// gets a bit from bitvector
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] >> (i % 8) & 0x1); // shift og vector right by offset, then && with 0x1
}


void bv_print(BitVector *v) {
    for (int i = 0; i < v->length; i++) {
        printf("%3" PRIu8, bv_get_bit(v, i));
    }
    printf("\n");    
}

