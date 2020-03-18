#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

namespace  benchmark {

    int quickSortPartition(int arr[], int start, int end);
    void quickSort(int *arr, int start, int end);

    void merge(int arr[], int start, int middle, int end);
    void mergeSort(int *arr, int left, int right);

    void selectionSort(int *arr, int size);

    void benchmarkMode();

}

