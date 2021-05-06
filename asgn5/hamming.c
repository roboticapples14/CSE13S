#include "hamming.h"
#include "bv.h"
#include "bm.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>



// Lookup table
// -2 = HAM_OK
// -1 = HAM_ERR
// n = bit number to be flipped
const int lookup[16] = {
    [0] = -2,  [1] = 4,  [2] = 5,  [3] = -1,
    [4] = 6,  [5] = -1,  [6] = -1,  [7] = 3,
    [8] = 7,  [9] = -1,  [10] = -1, [11] = 2,
    [12] = -1, [13] = 1, [14] = 0, [15] = -1,
};

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    // data in lower nibble of msg
    BitMatrix *msg_matrix = bm_from_data(msg, 4);
    BitMatrix *encoded = bm_multiply(msg_matrix, G);
    return bm_to_data(encoded);
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    HAM_STATUS status;
    uint32_t bit_to_flip;
    uint8_t err_syndrome;
    BitMatrix *code_matrix = bm_from_data(code, 8);
    // error syndrome = data of code_matrix * h^(transposed)
    err_syndrome = bm_to_data(bm_multiply(code_matrix, Ht));
    // if err_syndrome == 0000, status is HAM_OK
    int lookup_code = lookup[err_syndrome];
    if (lookup_code == -2) {
        status = HAM_OK;
    }
    // elif err_syndrome is non-zero and not in the Ht matrix, 
    // this indicates there's more than 1 error and we return HAM_ERR
    else if (lookup_code == -1) {
        status = HAM_ERR;
    }
    // else, resulting int corresponds to digit in msg that's been flipped
    // then need to flip it back to correct the code
    else {
	// if the error bit is currently 1, clear it to 0
        if (bm_get_bit(code_matrix, err_syndrome / 8, err_syndrome % 8) == 1) {
            bm_clr_bit(code_matrix, err_syndrome / 8, err_syndrome % 8);
	}
	// else if the error bit is currently 0, set it to 1
	else {
            bm_set_bit(code_matrix, err_syndrome / 8, err_syndrome % 8);
	}
	status = HAM_CORRECT;
    }
    // load corrected code matrix int msg
    *msg = bm_to_data(code_matrix); 
    return status;
}
