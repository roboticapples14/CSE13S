#include <unistd.h>
#include <fcntl.h>

// extern bytes_read;
// extern bytes_written;
static uint8_t buffer[BLOCK]; // contains bits
static int buffer_index = 0;


//TODO: THIS PROGRAM'S IN PROGRESS: FIX

// reads file until nbytes have been read or until there are no more bytes left to read
// returns number of bytes read
int read_bytes(int infile, uint8_t *buf, int nbytes) {

}

// write to file from buffer. Loops uitil nbytes were written or 
int write_bytes(int outfile, uint8_t *buf, int nbytes) {

}

bool read_bit(int infile, uint8_t *bit) {
    // reads into buffer
    // tracks buffer index into buffer and reads in 1 bit at a time
    // when buffer !full, fill it
}

// each bit in code c buffered until buffer is full, then write out entire buffer
void write_code(int outfile, Code *c) {
    for (int i = 0; i < c->top; i++) {
        // for every bit in c, if bit is 1, set bit in buffer, else clear it
	if (get_bit(c, i)) {
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
}
