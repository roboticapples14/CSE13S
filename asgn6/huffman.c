#include "huffman.h"
#include "huffman2.h"


Node *build_tree(uint64_t hist[static ALPHABET]) {

}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    // recursive call to post_order_traversal
    // should construct code as traversing through tree
    // and add code to table when leaf is reached
    post_order_traversal(root, c, table);
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

}

void delete_tree(Node **root) {

}


void post_order_traversal(Node *root, Code c, Code table[static ALPHABET]) {
    if (root->left != NULL) {
        uint8_t pop_bit;
	code_push_bit(c, 0); 				// add 0 to code for left traversal
	post_order_traversal(root->left, c, table); 	// recursive call to traversal on left branch
	code_pop_bit(c, pop_bit); 			// pop bit after recursing left
    }
    if (root->right != NULL) {
        uint8_t pop_bit;
	code_push_bit(c, 1); 				// add 1 to code for right traversal
	post_order_traversal(root->right, c, table); 	// recursive traversal on right branch
	code_pop_bit(c, pop_bit); 			// pop bit after recursing left
    }
    // if node is a leaf
    table[root->symbol] = c; // append code to cooresponding character spot in table
}
