#include "node.h"
#include "node2.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->oldspeak = strdup(oldspeak);
    n->newspeak = strdup(newspeak);
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void node_delete(Node **n) {
    if (*n) {
	free((*n)->oldspeak);
	(*n)->oldspeak = NULL;
	free((*n)->newspeak);
	(*n)->newspeak = NULL;
	free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n) {
    if (n->newspeak == NULL) {
        printf("(%s -> NULL)", n->oldspeak);
    }
    else {
        printf("(%s -> %s)", n->oldspeak, n->newspeak);
    }
}

// strdup code inspired by origional strdup source code
// Duplicate S, returning an identical malloc'd string.
char * strdup(const char *s) {
  size_t len = strlen(s) + 1;
  void *new = malloc (len);
  if (new == NULL)
    return NULL;
  return (char *) memcpy(new, s, len);
}
