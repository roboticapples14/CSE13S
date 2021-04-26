CC = clang  
CFLAGS = -Wall -Wextra  -Werror  -Wpedantic

all: sorting 

sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o   
	$(CC) -o sorting sorting.o bubble.o shell.o stack.o quick.o -lm
	
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.[ch]

clang-format:
	clang-format -i -style=file *.h *.c
	
scan -build: clean
	scan -build  make
