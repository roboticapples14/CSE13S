#include "shell.h"

#include "gaps.h"

#include <stdbool.h>
#include <stdlib.h>

static bool less_than(uint32_t el_1, uint32_t el_2);
int compares;
int moves;

// adopted from python psuedocode givein in asgn3 doc
void shell_sort(uint32_t *A, uint32_t n) {
    // Declares external variables compares and moves
    extern int compares;
    extern int moves;
    // resets compares and moves to 0
    compares = 0;
    moves = 0;

    // for gap in gaps
    for (uint32_t gap = 0; gap < sizeof(gaps); gap++) {
        //for i in range (gap, len(A))
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = A[i]; //move
            moves += 1;
            while (j >= gap && less_than(temp, A[j - gap])) {
                A[j] = A[j - gap]; //move
                moves += 1;
                j -= gap;
            }
            A[j] = temp; //move
            moves += 1;
        }
    }
}

/* comparison function, created to ensure that every time comparison is completed
that external var compares is itterated
Function idea inspired by Eugene's lab section 4/22 timestamp ~18:00 */
static bool less_than(uint32_t el_1, uint32_t el_2) {
    extern int compares;
    compares += 1;
    return el_1 < el_2;
}
