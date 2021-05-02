#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices; // Number of vertices.
    bool undirected; // Undirected graph?
    bool visited[VERTICES]; //Wherehavewegone?
    uint32_t matrix[VERTICES][VERTICES]; // Adjacency matrix.
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *g = (Graph *) calloc(VERTICES, sizeof(Graph));
    g->vertices = vertices; // num of vertices
    g->undirected = undirected;
    for (int i = 0; i < VERTICES; i++) {
        g->visited[i] = 0;
    }
    //calloc should already 0 matrix out but just in case
    for (int row = 0; row < VERTICES; row++) {
        for (int col = 0; col < VERTICES; col++) {
            g->matrix[row][col] = 0;
        }
    }
    return g;
}

void graph_delete(Graph **G) {
    // set pointer G to NULL
    G = NULL;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    // Is if(g) needed?
    if (G) {
        G->matrix[i][j] = k; //matrix[row][col] = weight
        // if matrix is undirected, add val to matrix[j][i]
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return 0;
    }
    return 1;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    // if matrix has a non-zero, positive weight
    return (G->matrix[i][j] > 0);
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (graph_has_edge(G, i, j)) {
        return G->matrix[i][j];
    }
    return 0;
}

bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    G->visited[v] = true;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    G->visited[v] = false;
}

//TODO
void graph_print(Graph *G) {
    printf("        ");
    for (uint32_t j = 0; j <= G->vertices; j++) {
        printf("%5" PRIu32, j);
    }
    printf("\n");
    printf("          ");
    for (uint32_t j = 0; j <= G->vertices; j++) {
        printf("  -  ");
    }
    printf("\n");

    for (uint32_t i = 0; i <= G->vertices; i++) {
        printf("%5" PRIu32, i);
        printf("  |");
        for (uint32_t j = 0; j <= G->vertices; j++) {
            printf("%5" PRIu32, graph_edge_weight(G, i, j));
        }
        printf("\n");
    }
}
