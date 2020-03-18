#include <iostream>
#include <random>
#include <thread>

namespace demo {

    int quickSortPartition(int arr[], int start, int end);
    void quickSort(int *arr, int start, int end);

    void merge(int arr[], int start, int middle, int end);
    void mergeSort(int *arr, int left, int right);

    void selectionSort(int *arr, int size);

    void combinationSort(int *arr, int size);

    void demoMode();

}