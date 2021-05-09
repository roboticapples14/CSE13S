#include "bm.h"

#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    int val = (rows * cols) % 8 == 0 ? (rows * cols) / 8 : (rows * cols) / 8 + 1;
    BitMatrix *bm = (BitMatrix *) calloc(val, sizeof(BitMatrix)); // size in bytes
    if (!bm) {
        return NULL;
    }
    bm->rows = rows;
    bm->cols = cols;
    bm->vector = bv_create(rows * cols);
    // clear every bit in matrix to 0
    for (uint32_t i = 0; i < bm->rows; i++) {
        for (uint32_t j = 0; j < bm->cols; j++) {
            bm_clr_bit(bm, i, j);
        }
    }
    return bm;
}

void bm_delete(BitMatrix **m) {
    // TODO:
    free((*m)->vector);
    free(*m);
    *m = NULL;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->cols + c); // set bit at index (r * cols + c)
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->cols + c); // clear bit at index (r * cols + c)
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * m->cols + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *bm = bm_create(1, length);
    // loop through all 8 bits
    for (uint32_t i = 0; i < length; i++) {
        // if bit at i is 1, set bit
        if (byte & (0x1 << i)) {
            bm_set_bit(bm, i / 8, i % 8);
        }
        // else clear bit
        else {
            bm_clr_bit(bm, i / 8, i % 8);
        }
    }
    return bm;
}

//TODO: right order from matrix to bin?
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t msg = 0;
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            msg |= bm_get_bit(m, i, j); // OR msg with bit at position (i, j)
            msg = msg << 1; // shift msg over 1 bit
        }
    }
    return msg;
}

//TODO: TEST
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *mult_result = bm_create(bm_rows(A), bm_cols(B));
    // cols of bm 1 has to == rows of bm 2
    if (A->cols != B->rows) {
        return NULL;
    }
    // XOR instead of +, & instead of multiply
    // ~ 20:00 in lecture 5/7
    else {
        // multiply matrices
        for (uint32_t i = 0; i < A->rows; i++) {
            for (uint32_t j = 0; j < B->cols; j++) {
                int sum = 0;
                for (uint32_t k = 0; k < A->cols; k++) {
                    sum += bm_get_bit(A, i, k) * bm_get_bit(B, k, j);
                }
                // if (A[i][j] * B[k][j]) % 2 == 1, set bit to 1
                if (sum % 2) {
                    bm_set_bit(mult_result, i, j);
                } else {
                    bm_clr_bit(mult_result, i, j);
                }
            }
        }
        return mult_result;
    }
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            printf("%d ", bm_get_bit(m, i, j));
            if (j == m->cols) {
                printf("\n");
            }
        }
    }
}
