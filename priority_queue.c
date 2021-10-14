#include "priority_queue.h"

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void sort(int *array, int array_size, int i) {
    if (array_size != 1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < array_size && array[left] > array[largest])
            largest = left;
        if (right < array_size && array[right] > array[largest])
            largest = right;
        if (largest != i) {
            swap(&array[i], &array[largest]);
            sort(array, array_size, largest);
        }
    }
}

void insert(int *array, int number, int *size) {
    if (*size == 0) {
        array[0] = number;
        *size += 1;
    } else {
        array[*size] = number;
        *size += 1;
        for (int i = *size / 2 - 1; i >= 0; i--) {
            sort(array, *size, i);
        }
    }
}
