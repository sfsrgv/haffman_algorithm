// Sofa Sergeeva
//
// Create program for coding and decoding text file using Haffman algorithm
//
// To compile program use command:
// gcc main.c minimum_heap.c char_reading.c queue.c make_codes.c leaves.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "char_reading.h"
#include "make_codes.h"
#include "leaves.h"

extern int heap_size;
extern struct symbol_code new_codes[ARRAY_SIZE];
extern int64_t real_tree_size;

#define BUFFER_LENGTH 10

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
            printf("Enter path to reading file: ");
            READ_LINE(reading_path);
        } else
            reading_path = argv[1];
        if (argc < 3) {
            printf("Enter path to writing file: ");
            READ_LINE(writing_path);
        } else
            writing_path = argv[2];
        printf("Enter operation (0 - code, 1 - decode): ");
        scanf("%d", &operation);
    }

    if (operation == 0) {
        // Coding text

        // Creating empty array_tree of nodes
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
            // Symbol of all nodes except leaves will be NULL to distinguish them
            new_node.symbol = '0';
            insert(heap, &new_node);
        }

        // Counting codes from tree
        make_codes(heap[1]);

        // Making file with code
        FILE *coding_file = fopen("code", "w");
        fprintf(coding_file, "%d\n", number_of_unique);
        tree_to_array(heap[1], 1, coding_file);

        //Print coded text to response file
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

    } else {
        //Decoding text

        // Getting code tree from file
        char prev_line[ARRAY_SIZE];
        char_auto_ptr line;
        struct leaf *leaves_indexes;
        size_t length = 0;
        int number_of_leaves;

        FILE *coding_file = fopen("code", "r");
        if (coding_file) {
            // Getting size of array
            getline(&line, &length, coding_file);
            line[strlen(line) - 1] = '\0';
            number_of_leaves = atoi(line);
            leaves_indexes = (struct leaf *) malloc(sizeof(struct leaf) * number_of_leaves);
            // Filling array with leaves of tree
            for (int i = 0; i < number_of_leaves; ++i) {
                getline(&line, &length, coding_file);
                line[strlen(line) - 1] = '\0';
                char symbol_string[BUFFER_LENGTH];
                strcpy(symbol_string, strchr(line, ' ') + 1);
                leaves_indexes[i].tree_index = atoi(line);
                leaves_indexes[i].symbol = (char) atoi(symbol_string);
            }
        } else
            return 1;
        fclose(coding_file);

        sort_by_index(leaves_indexes, 0, number_of_leaves - 1);

        // Decoding text
        FILE *file_read = fopen(reading_path, "r");
        FILE *file_write = fopen(writing_path, "w");
        char old_symbol;
        if (file_read && file_write)
            do {
                char new_symbol = '0';
                int coding_tree_position = 1;
                int leaves_position = 0;
                while (old_symbol != EOF) {
                    old_symbol = (char) getc(file_read);
                    coding_tree_position *= 2;
                    coding_tree_position += (old_symbol - '0');
                    while (leaves_indexes[leaves_position].tree_index < coding_tree_position)
                        ++leaves_position;
                    if (leaves_indexes[leaves_position].tree_index == coding_tree_position) {
                        new_symbol = leaves_indexes[leaves_position].symbol;
                        fprintf(file_write, "%c", new_symbol);
                        break;
                    }
                }
            } while (old_symbol != EOF);
        fclose(file_read);
        fclose(file_write);
    }
    return 0;
}

