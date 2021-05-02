CC = clang
CFLAGS = -Wall -Wextra  -Werror  -Wpedantic

all: tsp

tsp: tsp.o graph.o path.o stack.o
	$(CC) -o tsp tsp.o graph.o path.o stack.o -lm
        
tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f *.o tsp

format:
	clang-format -i -style=file *.[ch]

clang-format:
	clang-format -i -style=file *.h *.c
        
scan -build: clean
	scan -build  make
