#include "minimum_heap.h"

int heap_size = 0;
int64_t real_tree_size = 1;

void swap_nodes(struct heap_node *lhs, struct heap_node *rhs) {
    struct heap_node t;
    t = *lhs;
    *lhs = *rhs;
    *rhs = t;
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

void min_heapify(struct heap_node *heap[], int index) {
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

    // Smallest is not the heap_node, heap_node is not a heap
    if (smallest != index) {
        swap_nodes(heap[index], heap[smallest]);
        min_heapify(heap, smallest);
    }
}

struct heap_node *extract_min(struct heap_node *heap[]) {
    struct heap_node *minimum = heap[1];
    heap[1] = heap[heap_size];
    heap_size--;
    min_heapify(heap, 1);
    return minimum;
}

void decrease_key(struct heap_node *heap[], int index, int priority) {
    heap[index]->priority = priority;
    while ((index > 1) && (heap[get_parent(index)]->priority > heap[index]->priority)) {
        swap_nodes(heap[index], heap[get_parent(index)]);
        index = get_parent(index);
    }
}

void insert(struct heap_node *heap[], struct heap_node *key) {
    heap_size++;
    heap[heap_size] = malloc(sizeof(struct heap_node));
    heap[heap_size]->symbol = key->symbol;
    heap[heap_size]->right = key->right;
    heap[heap_size]->left = key->left;
    heap[heap_size]->priority = INF;
    decrease_key(heap, heap_size, key->priority);
}

void tree_to_file(struct heap_node *root, int node_number, FILE *file) {
    real_tree_size = real_tree_size < node_number ? node_number : real_tree_size;
    if (root->symbol != 0)
        fprintf(file, "%d %d\n", node_number, root->symbol);
    if (root->left != NULL) {
        tree_to_file(root->left, node_number * 2, file);
    }
    if (root->right != NULL) {
        tree_to_file(root->right, node_number * 2 + 1, file);
    }
}