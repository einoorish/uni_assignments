#include "DemoMode.h"

extern int* generateRandomArray(int size);
extern void printArray(int *arr, int size);

namespace demo {

    void demoMode() {

        int command;
        std::cout << std::endl << "1 - selection sort\n2 - quick sort\n3 - merge sort\n4 - combination sort" << std::endl;
        std::cin >> command;

        int *arr = generateRandomArray(10);
        std::cout << "Initial array: ";
        printArray(arr, 10);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        switch (command){
            case 1:
                selectionSort(arr, 10);
                break;

            case 2:
                std::cout << "Using Lomuto partition scheme (rightmost pivot) \n"
                             "take last element as pivot and place it at its correct position in a subarray sorted in a way that\n"
                             "all elements placed before the pivot are smaller and all elements placed after the pivot are bigger\n"
                             << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));

                quickSort(arr, 0, 9);
                break;

            case 3:
                mergeSort(arr, 0, 9);
                break;

            case 4:
                std::cout << "Combination Sort uses Selection Sort if array has <64 elements, otherwise it uses Quick Sort"<<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));

                combinationSort(arr,10);
                break;
        }

        std::cout << "result: ";
        printArray(arr, 10);
    }


    void selectionSort(int *arr, int size) {
        printArray(arr, size);
        int index_of_min = 0;
        std::cout << "current index of minimum element: " << index_of_min << ", minimum value: " << arr[index_of_min] << std::endl << std::endl;

        for (int i = 0; i < size - 1; i++) {
            index_of_min = i;

            std::cout << "looking for a min element in a subarray [" << i + 1 << ';' << size << ']' << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[index_of_min])
                    index_of_min = j;
            }

            std::cout << "found minimum element at index = " << index_of_min << ", value = " << arr[index_of_min]<< std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            std::cout << "swap it with the last element of the sorted part of the array" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            std::swap(arr[index_of_min], arr[i]);

            std::cout << "array after swapping: ";
            printArray(arr, size);
        }
    }


    int quickSortPartition(int arr[], int start, int end) {

        int pivot = arr[end];
        int new_pivot_position = start; // index of what should be the smallest element

        for (int i = start; i < end; i++) {
            if (arr[i] < pivot) {
                /*
                 * new_pivot_position starts to fall behind j when found arr.at(i) such that arr.at(i) >= pivot
                 * then this bigger value of arr.at(i) is swapped with next lesser than pivot laying in the interval [i, end]
                 * e.g. 1    2(new,i)  9          3     6    7(pivot)
                 *      1    2(new)    9(i)       3     6    7(pivot)              9 > 7 => new_pivot_position doesn't get changed
                 *      1    2         9(new)     3(i)  6    7(pivot)              3 < 7 => new_pivot_position gets incremented
                 *      1    2         3(new)     9(i)  6    7(pivot)              then 3 and 9 get swapped
                */
                std::swap(arr[new_pivot_position++], arr[i]);
            }
        }

        std::swap(arr[new_pivot_position], arr[end]);

        return new_pivot_position;
    }

    void quickSort(int *arr, int start, int end) {
        while (start < end) {
            std::cout << "in subarray: ["<<start<<';'<<end<<']'<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            int pivot = quickSortPartition(arr, start, end);

            std::cout << "pivot value : " << arr[pivot] << " new pivot index: "<<pivot<< std::endl;
            std::cout << "array after placing pivot at its correct position: ";
            printArray(arr, 10);
            std::this_thread::sleep_for(std::chrono::seconds(2));

            // tail call optimization to avoid stack overflow: recurse on smaller part, loop on larger part
            if (pivot - start <= end - pivot) {
                if(pivot!=0){
                    std::cout << "find pivot position in subarray ["<<start<<';'<<pivot-1<<']'<<std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }

                quickSort(arr, start, pivot - 1);
                start = pivot + 1;
            } else {
                std::cout << "find pivot position in subarray ["<<pivot+1<<';'<<end<<']'<<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));

                quickSort(arr, pivot + 1, end);
                end = pivot - 1;
            }
        }
    }


    void merge(int arr[], int start, int middle, int end) {
        int i = 0, j = 0;

        std::cout << "sorting subarrays ["<<start<<';'<<middle<<"] and ["<<middle+1<<';'<< end <<"]"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        int left_size = middle - start + 1;
        int right_size = end - middle;
        int left[left_size], right[right_size];

        for (; i < left_size; i++)
            left[i] = arr[start + i];
        for (; j < right_size; j++)
            right[j] = arr[middle + j + 1];

        std::cout << "\ncompare values in both arrays and put them in ascending order into the initial array"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));


        i = j = 0;
        int k = start; // starting index of merged subarray

        std::cout << "updated array values: ";

        while (i < left_size && j < right_size) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }

            std::cout << arr[k] << ' ';

            k++;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "\ncopy the remaining elements to the initial array if there are any "<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "updated array values: ";

        while (i < left_size) {
            arr[k] = left[i];

            std::cout << arr[k] << ' ';

            i++;
            k++;
        }

        while (j < right_size) {
            arr[k] = right[j];

            std::cout << arr[k] << ' ';

            j++;
            k++;
        }
    }

    void mergeSort(int *arr, int left, int right) {

        if (left < right) {
            int middle = left + (right - left) / 2;

            // sort left and right half separately
            std::cout << "sorting left half..." << std::endl;
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);

            merge(arr, left, middle, right);

            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << std::endl<< "result: ";
            printArray(arr, 10);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }


    void combinationSort(int *arr, int size) {
        if (size >= 64) quickSort(arr, 0, size - 1);
        else selectionSort(arr, size);
    }

}