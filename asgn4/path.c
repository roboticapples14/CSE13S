#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices; //The vertices comprising the path.
    uint32_t length; //The total length of the path.
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path)); //is this right?
    p->vertices = stack_create(VERTICES); //capacity = vertices
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    *p = NULL;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    // push v onto vertices stack if p exists and p->vertices not full
    if (p && !(stack_full(p->vertices))) {
        stack_push(p->vertices, v);

        // Add weight to path length
        // length += weight(last, current)
        // if nothing on the stack, the previous vertex was the origin
        if (stack_empty(p->vertices)) {
            //length += G->matrix[origin][v]
            p->length += graph_edge_weight(G, START_VERTEX, v);
        } else {
            // peek from stack to get previous vertex
            uint32_t x;
            stack_peek(p->vertices, &x);
            p->length += graph_edge_weight(G, x, v);
        }
        return true;
    }
    return false; // false if p doesn't exist
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    }
    stack_pop(p->vertices, v); // pops top vertex into v
    // If another element exists on stack, remove weight of them from length
    if (!stack_empty(p->vertices)) {
        uint32_t x;
        stack_peek(p->vertices, &x); // save next element in stack to x
        p->length -= graph_edge_weight(G, x, *v); // removes weight of edge from length
    }
    return true;
}

uint32_t path_vertices(Path *p) {
    //stack size
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    // print contents of path to outfile
    fprintf(outfile, "Path Print: \n");
    fprintf(outfile, "Path Length: %5" PRIu32, p->length);
    fprintf(outfile, "\n");
    stack_print(p->vertices, outfile, cities);
}
