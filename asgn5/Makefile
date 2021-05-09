CC = clang
CFLAGS = -Wall -Wextra  -Werror  -Wpedantic

all: encode decode error entropy

encode: encode.o bv.o bm.o hamming.o
	$(CC) -o encode encode.o bv.o bm.o hamming.o -lm

decode: decode.o bv.o bm.o hamming.o
	$(CC) -o decode decode.o bv.o bm.o hamming.o -lm

error: error.o
	$(CC) -o error error.o -lm

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

clean:
	rm -f *.o tsp

format:
	clang-format -i -style=file *.[ch]

clang-format:
	clang-format -i -style=file *.h *.c

scan -build: clean
	scan -build  make
