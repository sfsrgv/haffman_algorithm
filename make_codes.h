#ifndef HAFFMAN_ALGORITHM_MAKE_CODES_H
#define HAFFMAN_ALGORITHM_MAKE_CODES_H

#include "queue.h"
#include "binary_heap.h"

struct symbol_code {
    char symbol;
    char *code;
};

// Creates array of char symbols with their new codes from coding tree
void *make_codes(struct heap_node *tree_root);

#endif //HAFFMAN_ALGORITHM_MAKE_CODES_H
