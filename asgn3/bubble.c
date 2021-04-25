#include "bubble.h"
#include <stdlib.h>
#include <stdbool.h>

static bool less_than(uint32_t el_1, uint32_t el_2);
int compares;
int moves;

// adopted from python psuedocode givein in asgn3 doc
void bubble_sort(uint32_t *A, uint32_t n) {
    // Declares external variables compares and moves
    extern int compares;
    extern int moves;
    // resets compares and moves to 0
    compares = 0;
    moves = 0;
    int swapped = 1; //true
    while (swapped) {
        swapped = 0; //false
	for (uint32_t i = 1; i < n; i++) {
            if (less_than(A[i], A[i - 1])) { // using less_than function for compares increment
                uint32_t temp = A[i];
		A[i] = A[i - 1];
		A[i - 1] = temp;
		swapped = 1;
		moves += 3; //each swap is equivelent to 3 moves
            }
	}
	n -= 1;
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

