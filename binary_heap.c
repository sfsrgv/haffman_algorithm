#include "binary_heap.h"

int heap_size = 0;

void swap(struct node *a, struct node *b) {
    struct node t;
    t = *a;
    *a = *b;
    *b = t;
}

int get_right_child(int index) {
    if ((((2 * index) + 1) < ARRAY_SIZE) && (index >= 1))
        return (2 * index) + 1;
    return -1;
}

int get_left_child(int index) {
    if (((2 * index) < ARRAY_SIZE) && (index >= 1))
        return 2 * index;
    return -1;
}

int get_parent(int index) {
    if ((index > 1) && (index < ARRAY_SIZE)) {
        return index / 2;
    }
    return -1;
}

void min_heapify(struct node *heap[], int index) {
    int left_child_index = get_left_child(index);
    int right_child_index = get_right_child(index);

    // Finding smallest among index, left child and right child
    int smallest = index;
    if ((left_child_index <= heap_size) && (left_child_index > 0)) {
        if (heap[left_child_index]->priority < heap[smallest]->priority) {
            smallest = left_child_index;
        }
    }
    if ((right_child_index <= heap_size && (right_child_index > 0))) {
        if (heap[right_child_index]->priority < heap[smallest]->priority) {
            smallest = right_child_index;
        }
    }

    // Smallest is not the node, node is not a heap
    if (smallest != index) {
        swap(heap[index], heap[smallest]);
        min_heapify(heap, smallest);
    }
}

struct node *extract_min(struct node *heap[]) {
    struct node *minm = heap[1];
    heap[1] = heap[heap_size];
    heap_size--;
    min_heapify(heap, 1);
    return minm;
}

void decrease_key(struct node *heap[], int index, int priority) {
    heap[index]->priority = priority;
    while ((index > 1) && (heap[get_parent(index)]->priority > heap[index]->priority)) {
        swap(heap[index], heap[get_parent(index)]);
        index = get_parent(index);
    }
}

void insert(struct node *heap[], struct node *key) {
    heap_size++;
    heap[heap_size] = malloc(sizeof(struct node));
    heap[heap_size]->symbol = key->symbol;
    heap[heap_size]->right = key->right;
    heap[heap_size]->left = key->left;
    heap[heap_size]->priority = INF;
    decrease_key(heap, heap_size, key->priority);
}
