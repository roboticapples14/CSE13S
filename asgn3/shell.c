#include "shell.h"
#include "gaps.h"
#include <stdlib.h>

// adopted from python psuedocode givein in asgn3 doc
void shell_sort(uint32_t *A, uint32_t n) {
    // for gap in gaps
    for (int gap = 0; gap < sizeof(gaps); gap++) {
        //for i in range (gap, len(A))
	for (int i = gap; i < sizeof(A); i++) {
            int j = i;
	    int temp = arr[i];
	    while (j >= gap && temp < A[j - gap]) {
                A[j] = A[j - gap]
		j -= gap;
	    }
	    A[j] = temp;
	}
    }
}
