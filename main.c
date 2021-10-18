#include <stdio.h>
#include <string.h>

#include "char_reading.h"
#include "make_codes.h"

extern int heap_size;
extern struct symbol_code* new_codes;

int main(int argc, char **argv) {
    //Getting path to text file
    char_auto_ptr text_path;
    if (argc < 2) {
        printf("Enter path to text:\n");
        READ_LINE(text_path);
    } else
        text_path = argv[1];

    // Creating empty array of nodes
    struct heap_node nodes[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        nodes[i].symbol = (char) (i + 32);
        nodes[i].priority = 0;
        nodes[i].right = NULL;
        nodes[i].left = NULL;
    }

    // Counting frequency of symbols from text
    FILE *file = fopen(text_path, "r");
    char symbol;
    if (file != NULL) {
        do {
            symbol = (char) getc(file);
            ++nodes[(int) symbol - 32].priority;
        } while (symbol != EOF);
    }
    fclose(file);

    // Adding all symbols with frequency > 0 to heap
    int number_of_unique = 0;
    struct heap_node *heap[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i)
        if (nodes[i].priority) {
            insert(heap, &nodes[i]);
            ++number_of_unique;
        }

    // Creating coding tree
    while (heap_size > 1) {
        struct heap_node new_node;
        new_node.left = extract_min(heap);
        new_node.right = extract_min(heap);
        new_node.priority = new_node.left->priority + new_node.right->priority;
        // Symbol of all nodes except leaves will be 0 to distinguish them
        new_node.symbol = 0;
        insert(heap, &new_node);
    }

    new_codes = malloc(number_of_unique * sizeof(struct symbol_code));
    make_codes(heap[1]);

    for (int i = 0; i < number_of_unique; ++i) {
        printf("'%c' = %s\n", new_codes[i].symbol, new_codes[i].code);
    }

    return 0;
}
