#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "hamming2.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// h = help, i = infile, o = outfile
#define OPTIONS "hi:o:"

void print_instructions();
uint8_t G_arr[] = { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0,
    1, 1, 1, 1, 0 };

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int help = 0;
    int infile_given = 0;
    int outfile_given = 0;
    char input_byte; // where lines are stored
    BitMatrix *G = bm_create(4, 8);

    for (uint32_t i = 0; i < bm_rows(G); i++) {
        for (uint32_t j = 0; j < bm_cols(G); j++) {
            // if val of G_arr[index] is 1, set that bit to 1
            if (G_arr[(i * bm_cols(G)) + j] == 1) {
                bm_set_bit(G, i, j);
            }
            // else clear bit
            else {
                bm_clr_bit(G, i, j);
            }
        }
    }

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        // help menu
        if (opt == 'h') {
            help = 1;
        }
        // provided input file
        if (opt == 'i') {
            infile_given = 1;
            infile = fopen(optarg, "r"); //r for read
            if (infile == NULL) {
                fprintf(stderr, "failed to open input file");
                return 1;
            }
        }
        // provided output file
        if (opt == 'o') {
            outfile_given = 1;
            outfile = fopen(optarg, "w"); //w for write
            if (outfile == NULL) {
                fprintf(stderr, "failed to open output file");
                return 1;
            }
        }
	if (opt != 'o' && opt != 'i' && opt != 'h') {
            print_instructions();
	    return 1;
	}
    }
    if (help) {
        print_instructions();
	return 1;
    }
    //  Getting  and  setting  file  permissions
    if (infile_given && outfile_given) {
        struct stat statbuf;
        fstat(fileno(infile), &statbuf);
        fchmod(fileno(outfile), statbuf.st_mode);
    }

    while ((input_byte = fgetc(infile)) != EOF) {
        uint8_t lower = lower_nibble(input_byte);
        uint8_t upper = upper_nibble(input_byte);
        uint8_t code_lower = ham_encode(G, lower);
        fputc(code_lower, outfile);
        //printf("%" PRIu8, code_lower);
        uint8_t code_upper = ham_encode(G, upper);
        fputc(code_upper, outfile);
        //printf("%" PRIu8, code_upper);
    }
    
    // close any opened files
    if (infile_given) {
        fclose(infile);
    }
    if (outfile_given) {
       fclose(outfile);
    }
    // free allocated data
    bm_delete(&G);

    return 0;
}


void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("  A Hamming(8, 4) systematic code generator.\n\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.");
    printf("  -i infile      Input data to encode.\n");
    printf("  -o outfile     Output of encoded data.\n");
}
