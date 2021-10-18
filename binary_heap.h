#ifndef HAFFMAN_ALGORITHM_BINARY_HEAP_H
#define HAFFMAN_ALGORITHM_BINARY_HEAP_H

#include <stddef.h>
#include <stdio.h>
#include <malloc.h>

#define ARRAY_SIZE 95
#define INF 100000

struct node {
    char symbol;
    int priority;
    struct node *left;
    struct node *right;
};

// Swaps to nodes
void swap(struct node *a, struct node *b);

// Returns right child of a node of a tree
int get_right_child(int index);

// Returns left child of a node of a tree
int get_left_child(int index);

// Returns left parent of a node of a tree
int get_parent(int index);

// Sorting tree
void min_heapify(struct node *heap[], int index);

// Returns minimum value and delete it from heap
struct node *extract_min(struct node *heap[]);

// Changes priority of value at index
void decrease_key(struct node *heap[], int index, int priority);

// Inserting node to a tree
void insert(struct node *heap[], struct node *key);

#endif //HAFFMAN_ALGORITHM_BINARY_HEAP_H
