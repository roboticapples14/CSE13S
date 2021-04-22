#include "bubble.h"
#include "shell.h"
#include "quick.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "absqQrnp"

int main(int argc, char **argv) {
    int opt = 0;
    // int markers for which functions to run
    int bubble = 0;
    int shell = 0;
    int quick_stack = 0;
    int quick_queue = 0;
    int seed = 13371453;
    uint32_t size = 100;
    int elements = 100;

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        // sorts
	if (opt == 'a') {
            bubble = 1;
	    shell = 1;
	    quick_stack = 1;
	    quick_queue = 1;
	}
        if (opt == 'b') {
            bubble = 1;
	}
        if (opt == 's') {
            shell = 1;
	}
        if (opt == 'q') {
            quick_stack = 1;
	}
        if (opt == 'Q') {
            quick_queue = 1;
	}
	// output prefrences (optarg = value passed through with argument)
        if (opt == 'r') {
            seed = optarg;
	}
        if (opt == 'n') {
            size = optarg;
	}
        if (opt == 'p') {
            elements = optarg;
	}
	// if opt != any OPTIONS
	if (opt != 'a' && opt != 'b' && opt != 's' && opt != 'q' && opt != 'Q' && opt != 'r' && opt != 'n' && opt != 'p') {
	    // print error and instructions if user didn't enter valid input, then quit
            printf("./sorting: invalid option -- '%c'\n", opt);
	    print_instructions();
	    return 1;
	}
    }
    // if no sorting was selected
    if (!(bubble || shell || quick_stack || quick_queue))  {
	// Instructions
        printf("Select at least one sort to perform.\n");
        print_instructions();
	return 1;
    }

    // if elements to print is larger than size of array, set elements = size to prevent overflow 
    if (elements > size) {
        elements = size;
    }
    
    // Generates array to be sorted of len size
    uint32_t arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = random(); 
    }


    // Executes sorts
    if (bubble == 1) {
        printf("Bubble Sort\n");
        bubble_sort(arr, size);
	// TODO: implement moves, compares, and stack/queue size vars
	// Use extern vars?
	// printf("%i elements, %i moves, %i compares", elements, moves, compares);
        for (int j = 0; j < elements; j++) {
            if (j % 5) {
                printf("\n");
	    }
	    printf("%13" PRIu32, arr[j]);
	}
    }
    if (shell == 1) {
        printf("Shell Sort\n");
        shell_sort(arr, size);
	// TODO: implement moves, compares, and stack/queue size vars
	// Use extern vars?
	// printf("%i elements, %i moves, %i compares", elements, moves, compares);
        for (int j = 0; j < elements; j++) {
            if (j % 5) {
                printf("\n");
	    }
            printf("%13" PRIu32, arr[j]);
	}
    }

    if (quick_stack == 1) {
        printf("Quick Sort (Stack)\n");
        quick_sort_stack(arr, size);
	// TODO: implement moves, compares, and stack/queue size vars
	// Use extern vars?
	// printf("%i elements, %i moves, %i compares", elements, moves, compares);
        for (int j = 0; j < elements; j++) {
            if (j % 5) {
                printf("\n");
	    }
            printf("%13" PRIu32, arr[j]);
	}
    }
    if (quick_queue == 1) {
        printf("Quick Sort (Queue)\n");
        quick_sort_queue(arr, size);
	// TODO: implement moves, compares, and stack/queue size vars
	// Use extern vars?
	// printf("%i elements, %i moves, %i compares", elements, moves, compares);
        for (int j = 0; j < elements; j++) {
            if (j % 5) {
                printf("\n");
	    }
            printf("%13" PRIu32, arr[j]);
	}
    }
}



void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n");
    printf("   ./sorting [-absqQ] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -b              Enable Bubble Sort.\n");
    printf("   -s              Enable Shell Sort.\n");
    printf("   -q              Enable Quick Sort (Stack).\n");
    printf("   -Q              Enable Quick Sort (Queue).\n");
    printf("   -n length       Specify number of array elements.\n");
    printf("   -p elements     Specify number of elements to print.\n");
    printf("   -r seed         Specify random seed.\n");
}

