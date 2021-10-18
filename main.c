#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include <stdlib.h>

#include "char_reading.h"
#include "make_codes.h"

extern int heap_size;
extern struct symbol_code new_codes[ARRAY_SIZE];

int main(int argc, char **argv) {
    //Getting path to text file_read
    char_auto_ptr reading_path;
    char_auto_ptr writing_path;
    int operation;

    if (argc >= 4) {
        reading_path = argv[1];
        writing_path = argv[2];
        operation = atoi(argv[3]);
    } else {
        if (argc < 2) {
            reading_path = argv[1];
            printf("Enter path to reading file_read: ");
            READ_LINE(reading_path);
        } else
            reading_path = argv[1];
        if (argc < 3) {
            printf("Enter path to writing file_read: ");
            READ_LINE(writing_path);
        } else
            writing_path = argv[2];
        printf("Enter operation: ");
        scanf("%d", &operation);
    }

    // Creating empty array of nodes
    struct heap_node nodes[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        nodes[i].symbol = (char) i;
        nodes[i].priority = 0;
        nodes[i].right = NULL;
        nodes[i].left = NULL;

        new_codes[i].symbol = nodes[i].symbol;
        new_codes[i].code = 0;
    }

    // Counting frequency of symbols from text
    FILE *file_read = fopen(reading_path, "r");
    char symbol;
    if (file_read != NULL)
        do {
            symbol = (char) getc(file_read);
            ++nodes[(int) symbol].priority;
        } while (symbol != EOF);
    fclose(file_read);

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

    make_codes(heap[1]);

    printf("New codes:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i)
        if (new_codes[i].code)
            printf("'%c' = %s\n", new_codes[i].symbol, new_codes[i].code);

    file_read = fopen(reading_path, "r");
    FILE *file_write = fopen(writing_path, "w");
    if (file_read != NULL) {
        symbol = (char) getc(file_read);
        while (symbol != EOF) {
            for (int i = 0; i < strlen(new_codes[(int) symbol].code); ++i)
                fprintf(file_write, "%c", new_codes[(int) symbol].code[i]);
            symbol = (char) getc(file_read);
        }
    }
    fclose(file_read);
    fclose(file_write);
    return 0;
}
