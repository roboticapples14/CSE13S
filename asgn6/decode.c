#include "code.h"
#include "node.h"
#include "huffman.h"
#include "huffman2.h"
#include "defines.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "sys/stat.h"
#include "header.h"

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
int tree_size;


int main(int argc, char *argv[]) {
    int opt = 0;
    /*FILE *infile = stdin;
    FILE *outfile = stdout;*/
    char *infile;
    char *outfile;
    int fd_in = STDIN_FILENO;			// file descriptor for infile
    int fd_out = STDOUT_FILENO;			// file descriptor for outfile
    uint8_t buf[BLOCK];		// character buffer for reading and writing input/output
    int bytes_processed;	// holds return value of read_bytes() and write_bytes()
    int help = 0;
    int infile_given = 0;
    int outfile_given = 0;
    uint8_t bit;
    Code table[ALPHABET];	// table of cooresponding character codes

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
		//help menu
		case 'h':
			help = 1;
			break;
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
    

    // START DECODING PROCESS
    
    // READ HEADER
    Header h;
    read_bytes(fd_in, (uint8_t *) &h, sizeof(Header));
    if (h.magic != MAGIC) {
        dprintf(fd_out, "Input was not properly compressed with Huffman Encoder\n");
	return 1;
    }
    
    // set file permissions
    fchmod(fd_out, h.permissions);

    // RECREATE TREE
    // initialize tree_dump array
    uint8_t tree_dump[h.tree_size];

    //READ INPUT AND POPULATE HUFFMAN TREE ARRAY
    while ((bytes_processed = read_bytes(fd_in, buf, h.tree_size)) > 0) {
        // for each character in buffer
        for (int i = 0; i < bytes_processed; i++) {
            tree_dump[i] = buf[i];  // add char to tree_dump array
        }
    }
    // REBUILD TREE
    Node *root = rebuild_tree(tree_size, tree_dump);
    Node *cur = node_create(root->symbol, root->frequency);
    // use huffman tree to reconstruct origional messsage
    // itterate through each bit in input and traverse the tree until leaf is met
    while (read_bit(fd_in, &bit)) {
        if (root->left == NULL && root->right == NULL) {
            
	}
    }

}

void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("  A Huffman decoder.\n");
    printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
    
    printf("USAGE\n");
    printf("  ./decode [-h] [-v] [-i infile] [-o outfile]\n\n");
    
    printf("OPTIONS\n");
    printf("  -h             Program usage and help.");
    printf("  -v             Print decompression statistics.");
    printf("  -i infile      Input file to decompress.\n");
    printf("  -o outfile     Output of decompressed data.\n");
}
