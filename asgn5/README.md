Natalie Valett
nvalett
CSE13S Assignment 5: Hamming Codes


This lab’s objective is to produce an encoder and decoder for an (8,4) systematic hamming code. The encoder is able to take in any file as input and encrypt the binary one nibble at a time, each time returning a full byte containing the full encryption composed of 4 data bits and 4 parity bits.
The decoder should be able to then take an encrypted hamming file (such as one produced by the encoder) and decrypt each byte, determining in the process if there are any errors in the byte and correcting the errors if possible.

TO RUN:
After building the project by entering 'make' in the console, there should be TWO new executables in the directory called encode and decode. 

ENCODE:
To run the encoder enter "./encode [options]" in the terminal, where [options] include:
	-h: Prints out a help message for program usage
	-i infile: File to be encrypted. If not specified, defaults to stdin.
	-o outfile: File where encrypted output will be printed. If not specified, defaults to stdout.

DECODE:
To run the decoder enter "./decode [options]" in the terminal, where [options] include:
	-h: Prints out a help message for program usage
	-v: Enables verbose printing. If enabled, the program will print out decoding stats, such as bytes processed, bits corrected, uncorrected, and error rate.
	-i infile: File to be encrypted. If not specified, defaults to stdin.
	-o outfile: File where encrypted output will be printed. If not specified, defaults to stdout.
