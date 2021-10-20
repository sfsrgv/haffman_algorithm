#ifndef HAFFMAN_ALGORITHM_MINIMUM_HEAP_H
#define HAFFMAN_ALGORITHM_MINIMUM_HEAP_H

#include <stddef.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint-gcc.h>

#include "asprintf.h"

#define ARRAY_SIZE 255
#define INF 100000

struct heap_node {
    char symbol;
    int priority;
    struct heap_node *left;
    struct heap_node *right;
};

// Swaps to nodes
void swap_nodes(struct heap_node *lhs, struct heap_node *rhs);

// Returns right child of a heap_node of a tree
int get_right_child(int index);

// Returns left child of a heap_node of a tree
int get_left_child(int index);

// Returns left parent of a heap_node of a tree
int get_parent(int index);

// Sorting tree
void min_heapify(struct heap_node *heap[], int index);

// Returns minimum value and delete it from heap
struct heap_node *extract_min(struct heap_node *heap[]);

// Changes priority of value at index
void decrease_key(struct heap_node *heap[], int index, int priority);

// Inserting heap_node to a tree
void insert(struct heap_node *heap[], struct heap_node *key);

// Creating array version of code tree in order to write it file
void tree_to_file(struct heap_node *root, int node_number, FILE* file);

#endif //HAFFMAN_ALGORITHM_MINIMUM_HEAP_H
