CC = clang  
CFLAGS = -Wall -Wextra  -Werror  -Wpedantic

all: mathlib-test 

mathlib-test: mathlib-test.o mathlib.o     
	$(CC) -o mathlib-test mathlib-test.o mathlib.o -lm
	
mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

clean:
	rm -f *.o mathlib-test

clang-format:
	clang-format -i -style=file *.h *.c
	
scan -build: clean
	scan -build  make
