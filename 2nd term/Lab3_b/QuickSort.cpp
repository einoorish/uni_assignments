#include "QuickSort.h"

void swap(Item& a, Item& b){
    Item temp = a;
    a = b;
    b = temp;
}

int quickSortPartition(Item arr[], int (*comparator)(Item&, Item&), int start, int end) {

    Item pivot = arr[end];
    int new_pivot_position = start; // index of what should be the smallest element

    for (int i = start; i < end; i++) {
        if (comparator(arr[i], pivot)!=-1)
            swap(arr[new_pivot_position++], arr[i]);
    }

    swap(arr[new_pivot_position], arr[end]);

    return new_pivot_position;
}

void quickSort(Item* arr, int (*comparator)(Item&, Item&),  int start, int end) {
    while (start < end) {
        int pivot_position = quickSortPartition(arr, comparator,  start, end);

        if (pivot_position - start <= end - pivot_position) {
            quickSort(arr, comparator ,start, pivot_position - 1);
            start = pivot_position + 1;
        } else {
            quickSort(arr, comparator, pivot_position + 1, end);
            end = pivot_position - 1;
        }

    }
}


int quickSortPartition(Item arr[],
           int (*superComparator)(int (*comparators[])(Item&, Item&), int N, Item&, Item&),
           int (*comparators[])(Item&, Item&), int N, int start, int end) {

    Item pivot = arr[end];
    int new_pivot_position = start; // index of what should be the smallest element

    for (int i = start; i < end; i++) {
        if (superComparator(comparators, N, arr[i], pivot)==1)
            swap(arr[new_pivot_position++], arr[i]);
    }

    swap(arr[new_pivot_position], arr[end]);

    return new_pivot_position;
}

void quickSort(Item* arr,
               int (*superComparator)(int (*comparators[])(Item&, Item&), int N, Item&, Item&),
               int (*comparators[])(Item&, Item&), int N,  int start, int end) {
    while (start < end) {
        int pivot_position = quickSortPartition(arr, superComparator, comparators, N, start, end);

        if (pivot_position - start <= end - pivot_position) {
            quickSort(arr, superComparator, comparators , N, start, pivot_position - 1);
            start = pivot_position + 1;
        } else {
            quickSort(arr, superComparator, comparators, N, pivot_position + 1, end);
            end = pivot_position - 1;
        }

    }
}
