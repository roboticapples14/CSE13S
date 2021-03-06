#include "graph.h"
#include "path.h"
#include "path2.h"
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
int calls;
int n;

int main(int argc, char *argv[]) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char buffer[BLOCK];
    int help = 0;
    int undirected = 0;
    int infile_given = 0;
    int outfile_given = 0;
    int c; // where lines are stored
    extern int verbose;
    extern int calls; // num of recursive calls to dfs
    extern int n; // num of cities
    Path *current; //current path
    Path *shortest; //shortest path
    Graph *g; // create graph g of len n to populate with graph

    //user input loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
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
    c = fscanf(infile, "%i\n", &n); // set n to int on first line
    char *cities[n]; // array to hold city names, length of num of vertices
    // read in n city names
    for (int i = 0; i < n; i++) {
        fscanf(infile, "%s\n", buffer); // use fscanf instead of fgets to avoid newline problem
        cities[i] = strdup(buffer);
    }

    fscanf(infile, "");
    int vertex1, vertex2, weight; // i = vertex 1, j = vertex 2, k = weight
    g = graph_create(n, undirected); // create graph g of len n to populate with graph
    // read in edges and add to graph g
    while ((c = fscanf(infile, "%i %i %i\n", &vertex1, &vertex2, &weight)) != EOF) {
        if (c != 3) {
            printf("malformed line\n");
            return 1;
        }
        graph_add_edge(g, vertex1, vertex2, weight); // add given edge to graph g
    }

    current = path_create(); //current path
    shortest = path_create(); //shortest path
    calls = 1;
    //for (int vertex = START_VERTEX; vertex < n; vertex++) {
    // call depth first search on all vertices
    dfs(g, START_VERTEX, current, shortest, cities, outfile);
    //}

    // print results
    fprintf(outfile, "Shortest path length: %d\n", path_length(shortest));
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Number of recursive calls: %d\n", calls); // number of calls
    return 0;
}

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    extern int verbose;
    extern int calls; // num of recursive calls to dfs
    uint32_t popped_element;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);

    if (path_is_hamiltonian(curr, G)) {
        if (graph_has_edge(G, v, START_VERTEX)) {
            path_push_vertex(curr, START_VERTEX, G);

            if (path_length(shortest) == 0) {
                path_copy(shortest, curr);
            }
            if (verbose == true) {
                path_print(curr, outfile, cities);
            }
            if (path_length(curr) < path_length(shortest)) {
                path_copy(shortest, curr);
            }
        }
    }

    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (!graph_visited(G, i) && graph_has_edge(G, v, i)) {
            if (path_length(curr) <= path_length(shortest) || path_length(shortest) == 0) {
                dfs(G, i, curr, shortest, cities, outfile);
                calls++;
            }
        }
    }
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &popped_element, G);
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
