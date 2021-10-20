#ifndef HAFFMAN_ALGORITHM_LEAVES_H
#define HAFFMAN_ALGORITHM_LEAVES_H

struct leaf {
    int tree_index;
    char symbol;
};

// Swaps to leaves
void swap_leaves(struct leaf *lhs, struct leaf *rhs);

// Sorts leaves by 'tree_index'
void sort_by_index(struct leaf *leaves, int begin, int end);

#endif //HAFFMAN_ALGORITHM_LEAVES_H
