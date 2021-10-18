#include "queue.h"

void add(struct queue_node *root, int value) {
    struct queue_node *current = root;
    while (current->next != NULL) {
        current = current->next;
    }
    struct queue_node *new = malloc(sizeof(struct queue_node));
    new->value =value;
    new->next = NULL;
    current->next = new;
}

void delete(struct queue_node *root) {
    struct queue_node *current = root;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

char *make_line(struct queue_node *root) {
    char* line = ""; // if line = NULL return value starts with (null)
    struct queue_node *current = root->next;
    while (current != NULL) {
        asprintf(&line, "%s%d", line, current->value);
        current = current->next;
    }
    return line;
}