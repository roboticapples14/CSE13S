#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include "defines.h"
#include "code.h"
#include "code2.h"

// extern bytes_read;
// extern bytes_written;


//TESTED: working
// reads file until nbytes have been read or until there are no more bytes left to read
// returns number of bytes read
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes_read = 0;
    int n;
    while ((n = read(infile, buf, nbytes)) > 0 && bytes_read < nbytes) {
        bytes_read += n;
    }
    return bytes_read;
}

//TESTED: working
// write to file from buffer. Loops uitil nbytes were written and returns # bytes written
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes_written = 0;
    int n;
    while ((n = write(outfile, buf, nbytes)) > 0 && bytes_written < nbytes) {
        bytes_written += n;
    }
    return bytes_written;
}

//TODO
/*
bool read_bit(int infile, uint8_t *bit) {
    // reads into buffer
    // tracks buffer index into buffer and reads in 1 bit at a time
    // when buffer !full, fill it
}

// each bit in code c buffered until buffer is full, then write out entire buffer
void write_code(int outfile, Code *c) {
    for (int i = 0; i < c->top; i++) {
        // for every bit in c, if bit is 1, set bit in buffer, else clear it
	if (code_get_bit(c, i)) {
            set_bit(buffer, buffer_index);
	}
	else {
            clr_bit(buffer, buffer_index);
	}
	buffer_index += 1; 			// itterate buffer index
        // if buffer is full
	if (buffer_index == 8 * BLOCK) {
            write_bytes(outfile, buffer, BLOCK);// write buffer to outfile
	    buffer_index = 0; 			// reset buffer index
	}
    }    
}

//TODO: wtf
void flush_codes(int outfile) {
    if (buff_index != 0) {
        write_bytes(outfile, buffer, buff_index);
    }
}*/
