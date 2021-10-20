#include "leaves.h"

void swap_leaves(struct leaf *lhs, struct leaf *rhs) {
    struct leaf buffer = *lhs;
    *lhs = *rhs;
    *rhs = buffer;
}

void sort_by_index(struct leaf *leaves, int begin, int end) {
    int left = begin;
    int right = end;
    long long base = leaves[(begin + end) / 2].tree_index;
    do {
        while (leaves[left].tree_index < base)
            left++;
        while (leaves[right].tree_index > base)
            right--;
        if (left <= right) {
            if (leaves[left].tree_index > leaves[right].tree_index)
                swap_leaves(&leaves[left], &leaves[right]);
            left++;
            right--;
        }
    } while (left <= right);
    if (left < end)
        sort_by_index(leaves, left, end);
    if (begin < right)
        sort_by_index(leaves, begin, right);
}
