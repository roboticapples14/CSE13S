#include "ll.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//extern uint64_t seeks; // Number of seeks performed.
//extern uint64_t links; // Number of links traversed.

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf; 	// move to front flag
};


LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->tail->prev = ll->head;
    ll->head->next = ll->tail;
    ll->mtf = mtf;
    ll->length = 0;
    return ll;
}

void ll_delete(LinkedList **ll) {
    while ((*ll)->head != NULL) {
        Node *temp = (*ll)->head->next;
	node_delete(&(*ll)->head);
        (*ll)->head = temp;
    }
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

//TODO: this is causing segfault
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    // for each node in linked list
    for (Node *curr = ll->head; curr != NULL; curr = curr->next) {
        // if oldspeak of node matches searched oldspeak
	if (strcmp(curr->oldspeak, oldspeak) == 0) {
            // node was found, so if mtf enabled move queried node to front
            if (ll->mtf) {
	        // TODO: check if mtf logic correct
                curr->prev->next = curr->next;
	        curr->next->prev = curr->prev;
	        curr->next = ll->head->next;
	        curr->prev = ll->head;
	        ll->head->next = curr;
	        curr->next->prev = curr;
	    }
	    return curr;
	}
    }
    return NULL;
}

// insert node at head
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // seach linked list to see if oldspeak has already been inserted
    for (Node *curr = ll->head; curr != NULL; curr = curr->next) {
        if (strcmp(curr->oldspeak, oldspeak) == 0) {
            return;
	}
    }
    // insert node
    Node *n = node_create(oldspeak, newspeak);
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next = n;
    n->next->prev = n;
}

void ll_print(LinkedList *ll) {
    // for each node in list, print out node
    for (Node *curr = ll->head; curr != NULL; curr = curr->next) {
        node_print(curr);
	printf(", ");
    }
    printf("\n");
}
