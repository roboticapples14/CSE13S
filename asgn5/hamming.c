#include "hamming.h"

#include "bm.h"
#include "bv.h"
#include "hamming2.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Lookup table
// -3 = HAM_OK
// -2 = HAM_ERR
// n = bit number to be flipped
const int lookup[16] = {
    [0] = -3,
    [1] = 4,
    [2] = 5,
    [3] = -2,
    [4] = 6,
    [5] = -2,
    [6] = -2,
    [7] = 3,
    [8] = 7,
    [9] = -2,
    [10] = -2,
    [11] = 2,
    [12] = -2,
    [13] = 1,
    [14] = 0,
    [15] = -2,
};

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    // data in lower nibble of msg
    BitMatrix *msg_matrix = bm_from_data(lower_nibble(msg), 4);
    BitMatrix *encoded = bm_multiply(msg_matrix, G);
    return bm_to_data(encoded);
}

// if gets correctable error bit, flip bit and return corrected code into *msg
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    HAM_STATUS status;
    uint8_t err_syndrome;

    BitMatrix *code_matrix = bm_from_data(code, 8);
    
    // error syndrome = data of code_matrix * h^(transposed)
    err_syndrome = bm_to_data(bm_multiply(code_matrix, Ht));
    
    // indexes the lookup table with err syndrome
    int lookup_code = lookup[err_syndrome];
    
    // FOR DECODING:
    //printf("error syndrome: %" PRIu8 "\n", err_syndrome);    
    //printf("lookup code: %i\n", lookup_code);

    if (lookup_code == -3) {
        status = HAM_OK;
    }
    // elif err_syndrome is non-zero and not in the Ht matrix, there's more than 1 error and return HAM_ERR
    else if (lookup_code == -2) {
        status = HAM_ERR;
    }
    // else, resulting int corresponds to digit in msg that's been flipped
    // then need to flip it back to correct the code
    else {
        // if the error bit is currently 1, clear it to 0
        if (bm_get_bit(code_matrix, 0, lookup_code) == 1) {
            bm_clr_bit(code_matrix, 0, lookup_code % 8);
        }
        // else if the error bit is currently 0, set it to 1
        else {
            bm_set_bit(code_matrix, 0, lookup_code);
        }
        status = HAM_CORRECT;
    }
    // load corrected code matrix int msg
    *msg = bm_to_data(code_matrix);
    return status;
}

//  Returns  the  lower  nibble  of val
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

//  Returns  the  upper  nibble  of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

//  Packs  two  nibbles  into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}
