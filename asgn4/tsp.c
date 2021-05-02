#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK   4096
#define OPTIONS "hvui:o:"

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile);
bool path_is_hamiltonian(Path *p, Graph *G);
void print_instructions();
int verbose;

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *cities[VERTICES]; // array to hold city names, length of max amount of possible vertices
    char buffer[BLOCK];
    int help = 0;
    int undirected = 0;
    int infile_given = 0;
    int outfile_given = 0;
    int calls = 0; // number of recursive calls to dfs
    int n; // number of cities given in infile
    int c; // where lines are stored
    extern int verbose;
    Path *current; //current path
    Path *shortest; //shortest path
    Graph *g; // create graph g of len n to populate with graph


    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        assert(1 == 0);
        // help menu
        if (opt == 'h') {
            help = 1;
        }
        // verbose printing
        if (opt == 'v') {
            verbose = 1;
        }
        // undirected
        if (opt == 'u') {
            undirected = 1;
        }
        // provided input file
        if (opt == 'i') {
            infile_given = 1;
            infile = fopen(optarg, "r"); //r for read
            if (infile == NULL) {
                fprintf(stderr, "failed to open input file");
                return 1;
            }
        }
        // provided output file
        if (opt == 'o') {
            outfile_given = 1;
            outfile = fopen(optarg, "w"); //w for write
            if (outfile == NULL) {
                fprintf(stderr, "failed to open output file");
                return 1;
            }
        }
        // if opt != any OPTIONS
        if (opt != 'h' && opt != 'v' && opt != 'u' && opt != 'i' && opt != 'o') {
            // print error and instructions if user didn't enter valid input, then quit
            printf("./sorting: invalid option -- '%c'\n", opt);
            print_instructions();
            return 1;
        }
    }

    // once input options are determined, read first line
    c = fscanf(infile, "%i", &n); // set n to int on first line
    // for number of cities, read in name and store in cities array
    for (int i = 0; i < n; i++) {
        fgets(buffer, BLOCK, infile); // using fgets to store city name into city
        cities[i][strlen(cities[i]) - 1] = '\0'; //change last char from \n to \0 -> NEEDED FOR fgets()
    }
    int i, j, k;
    g = graph_create(n, undirected); // create graph g of len n to populate with graph
    // while ! end of file, read in next edge and add to graph g
    while ((c = fscanf(infile, "%i %i %i", &i, &j, &k)) != EOF) {
        if (c != 3) {
            printf("malformed line\n");
            return 1;
        }
        graph_add_edge(g, i, j, k); // add given edge to graph g
    }

    current = path_create(); //current path
    shortest = path_create(); //shortest path
    for (int vertex = START_VERTEX; vertex < n; vertex++) {
        // if outfile given, call dfs with outfile as file param
	if(outfile_given) {
            // call depth first search on all vertices
	    dfs(g, vertex, current, shortest, cities, outfile);
	}
        // if outfile NOT given, call dfs with stdout as default output
	else {
            // call depth first search on all vertices
	    dfs(g, vertex, current, shortest, cities, stdout);
	}
    }

    // print results
    // TODO: print results to stdout if no outfile specified
    fprintf(outfile, "Shortest path length: %d", path_length(shortest));
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Number of recursive calls: %d", calls); // number of calls
    return 0;
}

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    graph_mark_visited(G, v);
    if (path_is_hamiltonian(curr, G)) {
        // print every hamiltonian path if verbose option was chosen
        if (verbose == true) {
            path_print(curr, outfile, cities);
        }
        // if current path's length is shortest and shortest, copy current into shortest
        if (path_length(curr) < path_length(shortest)) {
            path_copy(shortest, curr);
        }
    }
    // for every vertex in graph that connects to v and is unvisited, call dfs on it
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (graph_has_edge(G, v, i) && !(graph_visited(G, v))) {
            uint32_t pop_contents;
            // push next vertex onto path
            path_push_vertex(curr, i, G);
            // recursive call to dfs
            dfs(G, i, curr, shortest, cities, outfile);
            // pop off stack after return from dfs
            path_pop_vertex(curr, &pop_contents, G);
        }
    }
    graph_mark_unvisited(G, v);
}

bool path_is_hamiltonian(Path *p, Graph *G) {
    // path is hamiltonian if number of vertices is equal to num of vertices in graph
    return path_vertices(p) == graph_vertices(G);
}

void print_instructions() {
    // Instructions
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -u             Use undirected graph.\n");
    printf("  -v             Enable verbose printing.\n");
    printf("  -h             Program usage and help.\n");
    printf("  -i infile      Input containing graph (default: stdin)\n");
    printf("  -o outfile     Output of computed path (default: stdout)\n");
}
