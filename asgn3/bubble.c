#include "bubble.h"
#include <stdlib.h>

// adopted from python psuedocode givein in asgn3 doc
void bubble_sort(uint32_t *A, uint32_t n) {
    int swapped = 1; //true
    while (swapped) {
        swapped = 0; //false
	for (int i = 1; i < n; i++) {
            if (A[i] < A[i - 1]) {
                uint32_t temp = A[i];
		A[i] = A[i - 1];
		A[i - 1] = temp;
		swapped = true;
            }
	}
	n -= 1;
    }
}
