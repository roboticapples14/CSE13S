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
#include <fcntl.h>

// h = help, i = infile, o = outfile, v = verbose
#define OPTIONS "hvi:o:"

void print_instructions();

int main(int argc, char *argv[]) {
    int opt = 0;
    /*FILE *infile = stdin;
    FILE *outfile = stdout;*/
    char *infile;
    char *outfile;
    int fd_in;			// file descriptor for infile
    int fd_out;			// file descriptor for outfile
    uint8_t buf[BLOCK];		// character buffer for reading and writing input/output
    int bytes_processed;	// holds return value of read_bytes() and write_bytes()
    int help = 0;
    int verbose = 0;
    int infile_given = 0;
    int outfile_given = 0;
    uint64_t hist[ALPHABET]; 	// histogram of character frequencies
    Code table[ALPHABET];	// table of cooresponding character codes

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
			// open input file
                        infile = optarg;
			fd_in = open(infile, O_RDONLY, 0); 
                        // error opening if open returns -1
			if (fd_in == -1) {
                		fprintf(stderr, "failed to open input file");
                		return 1;
			}
			break;
		case 'o':
			outfile_given = 1;
			// open output file
                        outfile = optarg;
			fd_out = open(outfile, O_WRONLY, 0); 
                        // error opening if open returns -1
			if (fd_in == -1) {
                		fprintf(stderr, "failed to open input file");
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
    //TODO: FIX
    /*if (infile_given && outfile_given) {
        struct stat statbuf;
        fstat(fileno(fd_in), &statbuf);
        fchmod(fileno(fd_out), statbuf.st_mode);
    }*/

    // START ENCODING PROCESS
    
    //zero out histogram
    for (int i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }

    //READ INPUT AND POPULATE HIST
    while ((bytes_processed = read_bytes(fd_in, buf, BLOCK)) > 0) {
        // for each character in buffer
        for (int i = 0; i < bytes_processed; i++) {
            hist[buf[i]] += 1;	// increment counter of hist at character read
        }
    }

    // build Huffman tree from histogram
    Node *root = build_tree(hist);

    // INITIATE CODE TABLE
    for (int i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }
    // populate code table with char codes from tree
    build_codes(root, table);



    for (int i = 0; i < ALPHABET; i++) {
        if (!code_empty(&table[i])) {
            printf("%i: ", i);
            code_print(&(table[i]));
            printf("\n");
        }
    }



    // close any opened files
    if (infile_given) {
        close(fd_in);
    }
    if (outfile_given) {
        close(fd_out);
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
