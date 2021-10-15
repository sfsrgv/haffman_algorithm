#ifndef HAFFMAN_ALGORITHM_PRIORITY_QUEUE_H
#define HAFFMAN_ALGORITHM_PRIORITY_QUEUE_H

struct Node {
    int priority;
    char symbol;
    struct Node *left;
    struct Node *right;
};

void swap(struct Node *a, struct Node *b);

void sort_by_priority(struct Node *nodes, int begin, int end);

void insert(struct Node *array, struct Node node, int *size);


#endif //HAFFMAN_ALGORITHM_PRIORITY_QUEUE_H
