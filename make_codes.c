#include "make_codes.h"

struct queue_node current_code = {0, NULL};
struct symbol_code new_codes[ARRAY_SIZE];

void *make_codes(struct heap_node *tree_root) {
    if (tree_root) {
        if (tree_root->symbol != 0)
            new_codes[(int)tree_root->symbol].code = make_line(&current_code);
        add(&current_code, 0);
        make_codes(tree_root->left);
        delete(&current_code);

        add(&current_code, 1);
        make_codes(tree_root->right);
        delete(&current_code);
    }
}