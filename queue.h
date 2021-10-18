#ifndef HAFFMAN_ALGORITHM_QUEUE_H
#define HAFFMAN_ALGORITHM_QUEUE_H

#include <stddef.h>
#include <malloc.h>

#include "asprintf.h"

struct queue_node {
    int value;
    struct queue_node *next;
};

// Adds to queue
void add(struct queue_node *root, int value);

// Deletes last in queue
void delete(struct queue_node *root);

// Returns line of values from queue
char *make_line(struct queue_node *root);

#endif //HAFFMAN_ALGORITHM_QUEUE_H
