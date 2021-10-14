#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 95

struct symbol_frequency {
    char symbol;
    int frequency;
};

void swap_symbols(struct symbol_frequency *lhs, struct symbol_frequency *rhs) {
    struct symbol_frequency temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void sort_by_frequency(struct symbol_frequency *symbols, int begin, int end) {
    int left = begin;
    int right = end;
    long long base = symbols[(begin + end) / 2].frequency;
    do {
        while (symbols[left].frequency > base)
            left++;
        while (symbols[right].frequency < base)
            right--;
        if (left <= right) {
            if (symbols[left].frequency < symbols[right].frequency)
                swap_symbols(&symbols[left], &symbols[right]);
            left++;
            right--;
        }
    } while (left <= right);
    if (left < end)
        sort_by_frequency(symbols, left, end);
    if (begin < right)
        sort_by_frequency(symbols, begin, right);
}

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

    FILE *file = fopen(text_path, "r");
    char symbol;
    struct symbol_frequency symbol_frequencies[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        symbol_frequencies[i].symbol = (char) (i + 32);
        symbol_frequencies[i].frequency = 0;
    }

    if (file != NULL) {
        do {
            symbol = (char) getc(file);
            symbol_frequencies[(int) symbol - 32].frequency++;
        } while (symbol != EOF);
    }

    sort_by_frequency(symbol_frequencies, 0, ARRAY_SIZE - 1);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (symbol_frequencies[i].frequency) {
            printf("%d: %c: %d\n", i, symbol_frequencies[i].symbol, symbol_frequencies[i].frequency);
        } else
            break;
    }

}
