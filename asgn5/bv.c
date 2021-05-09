#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length; //  Length  in bits.
    uint8_t *vector; // Array of bytes.
};

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector)); // 1 refers to 1 byte
    if (!v) {
        return NULL;
    }
    v->length = length;
    // if not divisible by 8, needs 1 extra byte to hold length
    int val = length % 8 == 0 ? length / 8 : length / 8 + 1;
    v->vector
        = (uint8_t *) calloc(val, sizeof(uint8_t)); // length is in bits, need to convert to bytes
    if (!v->vector) {
        return NULL;
    }
    return v;
}

// frees memory allocated for BitVector
void bv_delete(BitVector **v) {
    free((*v)->vector);
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
    //set bit at i to 1 and or with og data
    v->vector[i / 8] |= (0x1 << (i % 8)); // || og byte with 00..1..00
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
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%3" PRIu8, bv_get_bit(v, i));
    }
    printf("\n");
}
