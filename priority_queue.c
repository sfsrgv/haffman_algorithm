#include "priority_queue.h"


void swap(struct Node *a, struct Node *b) {
    struct Node temp = *b;
    *b = *a;
    *a = temp;
}

void sort_by_priority(struct Node *nodes, int begin, int end) {
    int left = begin;
    int right = end;
    long long base = nodes[(begin + end) / 2].priority;
    do {
        while (nodes[left].priority < base)
            left++;
        while (nodes[right].priority > base)
            right--;
        if (left <= right) {
            if (nodes[left].priority > nodes[right].priority)
                swap(&nodes[left], &nodes[right]);
            left++;
            right--;
        }
    } while (left <= right);
    if (left < end)
        sort_by_priority(nodes, left, end);
    if (begin < right)
        sort_by_priority(nodes, begin, right);
}

void insert(struct Node *array, struct Node node, int *size) {
    if (*size == 0) {
        array[0] = node;
    } else {
        array[*size] = node;
        sort_by_priority(array, 0, *size);
    }
    ++(*size);
}
