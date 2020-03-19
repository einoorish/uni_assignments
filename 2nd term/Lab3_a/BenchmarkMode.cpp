#include <algorithm>
#include "BenchmarkMode.h"


extern int* generateRandomArray(int size);

namespace benchmark {

    //passed as argument to testSort(...) in order to fit "void (*sort)(int* arr, int size)" pattern
    void librarySort(int arr[], int size){
        std::sort(arr, arr+size);
    }

    //passed as argument to testSort(...) in order to fit "void (*sort)(int* arr, int size)" pattern
    void quickSort(int arr[], int size) {
        quickSort(arr, 0, size - 1);
    }

    //passed as argument to testSort(...) in order to fit "void (*sort)(int* arr, int size)" pattern
    void mergeSort(int arr[], int size) {
        mergeSort(arr, 0, size - 1);
    }

    //returns time it took to sort an array
    double testSort(void (*sort)(int *, int), int *arr, int size) {

        unsigned int delta = clock();
        sort(arr, size);
        delta = clock() - delta;

        return (double) delta / CLOCKS_PER_SEC;
    }

    //passes array copy to testSort and outputs the result into file
    void benchmarkHelper(std::ofstream &fout, int N, int arr[], void (*sort)(int *, int), const char sortingName[],
                         const char arrayType[]) {

        //only the copy will get modified, so the original can be further used while testing another sorting
        int *arrCopy = new int[N];
        std::copy(arr, arr + N, arrCopy);

        fout << std::endl << sortingName << " FOR ARRAY OF " << N << " " << arrayType << std::endl;

        fout << "Sorting took " << testSort(sort, arrCopy, N) << std::endl;

        delete[] arrCopy;
    }


    void benchmarkMode() {
        std::ofstream fout("benchmark_results.txt", std::ios::out);
        std::cout << "1/3 Testing random arrays of size 1000, 10000 and 100000..." <<std::endl;
        fout << "\n--------------------------------------- Random array --------------------------------------- \n\n";

        int size = 1000;
        int *arr = generateRandomArray(size);

        benchmarkHelper(fout, size, arr, selectionSort, "SELECTION SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "RANDOM ELEMENTS");

        fout << "\n-------------------------- \n" << std::endl;

        size = 10000;
        delete[] arr;
        arr = generateRandomArray(size);

        benchmarkHelper(fout, size, arr, selectionSort, "SELECTION SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "RANDOM ELEMENTS");

        fout << "\n-------------------------- \n" << std::endl;

        size = 100000;
        delete[] arr;
        arr = generateRandomArray(size);

        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "RANDOM ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "RANDOM ELEMENTS");

        std::cout << "2/3 Testing almost sorted arrays of size 1000, 10000 and 100000..." <<std::endl;
        fout<< "\n--------------------------------------- Almost sorted array --------------------------------------- \n\n";

        size = 1000;
        delete[] arr;
        arr = new int[size];
        for (int i = 0; i < size; i++) { arr[i] = i; }
        std::swap(arr[44], arr[3]);
        std::swap(arr[244], arr[size - 3]);
        std::swap(arr[7], arr[793]);

        benchmarkHelper(fout, size, arr, selectionSort, "SELECTION SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "ALMOST SORTED ELEMENTS");

        fout << "\n-------------------------- \n" << std::endl;

        size = 10000;
        delete[] arr;
        arr = new int[size];
        for (int i = 0; i < size; i++) { arr[i] = i; }
        std::swap(arr[44], arr[3]);
        std::swap(arr[244], arr[size - 3]);
        std::swap(arr[7], arr[793]);

        benchmarkHelper(fout, size, arr, selectionSort, "SELECTION SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "ALMOST SORTED ELEMENTS");

        fout << "\n-------------------------- \n" << std::endl;

        size = 100000;
        delete[] arr;
        arr = new int[size];
        for (int i = 0; i < size; i++) { arr[i] = i; }
        std::swap(arr[44], arr[3]);
        std::swap(arr[244], arr[size - 3]);
        std::swap(arr[7], arr[793]);

        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "ALMOST SORTED ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "ALMOST SORTED ELEMENTS");

        std::cout << "3/3 Testing reversed sorted arrays of size 1000, 10000 and 100000..." <<std::endl;
        fout << "\n--------------------------------------- Reversed array--------------------------------------- \n\n";

        delete[] arr;
        size = 1000;
        arr = new int[size];
        for (int i = 0; i < size; i++) { arr[i] = size - i; }

        benchmarkHelper(fout, size, arr, selectionSort, "SELECTION SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "REVERSE ORDERED ELEMENTS");

        fout << "\n-------------------------- \n" << std::endl;

        delete[] arr;
        size = 10000;
        arr = new int[size];
        for (int i = 0; i < size; i++) { arr[i] = size - i; }

        benchmarkHelper(fout, size, arr, selectionSort, "SELECTION SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "REVERSE ORDERED ELEMENTS");

        fout << "\n-------------------------- \n" << std::endl;

        delete[] arr;
        size = 100000;
        arr = new int[size];
        for (int i = 0; i < size; i++) { arr[i] = size - i; }

        benchmarkHelper(fout, size, arr, quickSort, "QUICK SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, mergeSort, "MERGE SORT", "REVERSE ORDERED ELEMENTS");
        benchmarkHelper(fout, size, arr, librarySort, "STL SORT", "REVERSE ORDERED ELEMENTS");
        fout.close();
        std::cout << "Benchmark finished. See results in \"benchmark_results.txt\"" <<std::endl;
    }


    void selectionSort(int *arr, int size) {
        int index_of_min = 0;

        for (int i = 0; i < size - 1; i++) {
            index_of_min = i;

            for (int j = i + 1; j < size; j++)
                // looking for a min element in a subarray [i; size]
                if (arr[j] < arr[index_of_min])
                    index_of_min = j;

            // swap the found min and first element of the subarray
            std::swap(arr[index_of_min], arr[i]);
        }
    }


    int quickSortPartition(int arr[], int start, int end) {
        /*
         * Lomuto partition scheme, rightmost pivot
         * takes last element as pivot and places it at its correct position in a subarray sorted in a way that
         * all elements placed before the pivot are smaller and all elements placed after the pivot are bigger
        */

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
            int pivot = quickSortPartition(arr, start, end);

            // tail call optimization to avoid stack overflow: recurse on smaller part, loop on larger part
            if (pivot - start <= end - pivot) {
                quickSort(arr, start, pivot - 1);
                start = pivot + 1;
            } else {
                quickSort(arr, pivot + 1, end);
                end = pivot - 1;
            }

        }
    }


    void merge(int arr[], int start, int middle, int end) {
        int i = 0, j = 0;

        int left_size = middle - start + 1;
        int right_size = end - middle;
        int left[left_size], right[right_size];

        for (; i < left_size; i++)
            left[i] = arr[start + i];
        for (; j < right_size; j++)
            right[j] = arr[middle + j + 1];

        // compare values in both arrays and put them in ascending order into the initial subarray
        i = j = 0;
        int k = start; // starting index of merged subarray
        while (i < left_size && j < right_size) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        // copy the remaining elements if there are any
        while (i < left_size) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < right_size) {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

    void mergeSort(int *arr, int left, int right) {

        if (left < right) {
            int middle = left + (right - left) / 2;

            // sort left and right half separately
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);

            merge(arr, left, middle, right);
        }
    }

}