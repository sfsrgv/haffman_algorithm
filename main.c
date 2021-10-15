#include <stdio.h>
#include <string.h>

#include "asprintf.h"

#define ARRAY_SIZE 95

struct node {
    char symbol;
    int priority;
    struct node *left;
    struct node *right;
};

int tree_array_size = 20;
int heap_size = 0;
const int INF = 100000;

void swap(struct node *a, struct node *b) {
    struct node t;
    t = *a;
    *a = *b;
    *b = t;
}

//function to get right child of a node of a tree
int get_right_child(struct node A[], int index) {
    if ((((2 * index) + 1) < tree_array_size) && (index >= 1))
        return (2 * index) + 1;
    return -1;
}

//function to get left child of a node of a tree
int get_left_child(struct node A[], int index) {
    if (((2 * index) < tree_array_size) && (index >= 1))
        return 2 * index;
    return -1;
}

//function to get the parent of a node of a tree
int get_parent(struct node A[], int index) {
    if ((index > 1) && (index < tree_array_size)) {
        return index / 2;
    }
    return -1;
}

void min_heapify(struct node A[], int index) {
    int left_child_index = get_left_child(A, index);
    int right_child_index = get_right_child(A, index);

    // finding smallest among index, left child and right child
    int smallest = index;

    if ((left_child_index <= heap_size) && (left_child_index > 0)) {
        if (A[left_child_index].priority < A[smallest].priority) {
            smallest = left_child_index;
        }
    }

    if ((right_child_index <= heap_size && (right_child_index > 0))) {
        if (A[right_child_index].priority < A[smallest].priority) {
            smallest = right_child_index;
        }
    }

    // smallest is not the node, node is not a heap
    if (smallest != index) {
        swap(&A[index], &A[smallest]);
        min_heapify(A, smallest);
    }
}

void build_min_heap(struct node A[]) {
    int i;
    for (i = heap_size / 2; i >= 1; i--) {
        min_heapify(A, i);
    }
}

struct node minimum(struct node A[]) {
    return A[1];
}

struct node extract_min(struct node A[]) {
    struct node minm = A[1];
    A[1] = A[heap_size];
    heap_size--;
    min_heapify(A, 1);
    return minm;
}

void decrease_key(struct node A[], int index, int key) {
    A[index].priority = key;
    while ((index > 1) && (A[get_parent(A, index)].priority > A[index].priority)) {
        swap(&A[index], &A[get_parent(A, index)]);
        index = get_parent(A, index);
    }
}

void increase_key(struct node A[], int index, int key) {
    A[index].priority = key;
    min_heapify(A, index);
}

void insert(struct node A[], struct node key) {
    heap_size++;
    A[heap_size].symbol = key.symbol;
    A[heap_size].right = key.right;
    A[heap_size].left = key.left;
    A[heap_size].priority = INF;
    decrease_key(A, heap_size, key.priority);
}

void print_node(struct node node) {
    char left = (node.left != NULL) ? node.left->symbol : 'n';
    char right = (node.right != NULL) ? node.right->symbol : 'n';
    printf("%d: %c (left: %c) (right: %c)\n", node.priority, node.symbol,
           left, right);
}


void print_heap(struct node A[]) {
    int i;
    for (i = 1; i <= heap_size; i++) {
        print_node(A[i]);
    }
    printf("\n");
}

struct new_code {
    char symbol;
    char *code;
};

int main(int argc, char **argv) {
    //Getting path to text file
    char *text_path;
    size_t length = 0;
    if (argc < 2) {
        printf("Enter path to text:\n");
        getline(&text_path, &length, stdin);
        text_path[strlen(text_path) - 1] = '\0';
    } else
        text_path = argv[1];

    struct node nodes[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        nodes[i].symbol = (char) (i + 32);
        nodes[i].priority = 0;
        nodes[i].right = NULL;
        nodes[i].left = NULL;
    }

    int size = 0;
    FILE *file = fopen(text_path, "r");
    char symbol;
    if (file != NULL) {
        do {
            symbol = (char) getc(file);
            nodes[(int) symbol - 32].priority++;
            ++size;
        } while (symbol != EOF);
    }

    struct node heap[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (nodes[i].priority) {
            printf("inserted: %c\n", nodes[i].symbol);
            insert(heap, nodes[i]);
        }
    }

    while (heap_size > 1) {
        struct node first = extract_min(heap);
        struct node second = extract_min(heap);
        struct node new_node;
        new_node.priority = first.priority + second.priority;
        new_node.left = &first;
        new_node.right = &second;
        new_node.symbol = 0;
        insert(heap, new_node);
        print_heap(heap);
    }
}
