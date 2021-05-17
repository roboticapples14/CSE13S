#include "code.h"
#include "node.h"
#include "huffman.h"
#include "huffman2.h"
#include "defines.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "sys/stat.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// h = help, i = infile, o = outfile, v = verbose
#define OPTIONS "hvi:o:"

void print_instructions();

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int help = 0;
    int verbose = 0;
    int infile_given = 0;
    int outfile_given = 0;
    char input_byte; 		// where lines are stored
    uint64_t hist[ALPHABET]; 	// histogram of character frequencies
    Code table[ALPHABET]	// table of cooresponding character codes

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
		//help menu
		case 'h':
			help = 1;
			break;
		// verbpse: print compression stats
		case 'v':
			verbose = 1;
			break;
		case 'i':
			infile_given = 1;
                        infile = fopen(optarg, "r"); //r for read
                        if (infile == NULL) {
                		fprintf(stderr, "failed to open input file");
                		return 1;
			}
			break;
		case 'o':
            		outfile_given = 1;
            		outfile = fopen(optarg, "w"); //w for write
            		if (outfile == NULL) {
                		fprintf(stderr, "failed to open output file");
                		return 1;
			}
			break;
		default:
			print_instructions();
            		break;
        }
    }
    if (help) {
        print_instructions();
        return 1;
    }
    
    //  Getting  and  setting  file  permissions
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    //READ INPUT AND CONSTRUCT HIST
    read_bytes();


    // START ENCODING PROCESS
    
    //zero out histogram
    for (int i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }
    //read in input


    while ((input_byte = fgetc(infile)) != EOF) {
        fputc(code_lower, outfile);
        fputc(code_upper, outfile);
    }

    // close any opened files
    if (infile_given) {
        fclose(infile);
    }
    if (outfile_given) {
        fclose(outfile);
    }
    // free allocated data

    return 0;
}

void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder.\n");
    printf("  Compresses a file using the Huffman coding algorithm.\n\n");
    
    printf("USAGE\n");
    printf("  ./encode [-h] [-v] [-i infile] [-o outfile]\n\n");
    
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.");
    printf("  -v             Print compression statistics.");
    printf("  -i infile      Input data to encode.\n");
    printf("  -o outfile     Output of encoded data.\n");
}
