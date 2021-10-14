#include <stdio.h>

#include "priority_queue.h"

int main() {
    int array[10];
    int size = 0;
    insert(array, 3, &size);
    insert(array, 4, &size);
    insert(array, 3, &size);
    insert(array, 5, &size);
    insert(array, 2, &size);
    printf("max-heap: ");
    for (int i = size - 1; i >= 0; --i)
        printf("%d ", array[i]);
    printf("\n");

}
