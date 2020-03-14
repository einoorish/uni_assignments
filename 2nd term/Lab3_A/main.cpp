#include <iostream>
#include <random>
#include <chrono>

void swap(int *first, int *second){
    int temp = *first;
    *first = *second;
    *second = temp;
}

int quickSortPartition(int arr[], int start, int end);
void mergeSortPartition(int* arr, int start, int middle, int end);
void quickSort(int arr[], int start, int end);
void mergeSort(int* arr, int left, int right);
void selectionSort(int* arr, int size){
    int index_of_min = 0;

    for (int i = 0; i < size-1; i++)
    {
        index_of_min = i;

        for (int j = i+1; j < size; j++)
            // looking for a min element in a subarray [i; size]
            if (arr[j] < arr[index_of_min])
                index_of_min = j;

        // swap the found min and first element of the subarray
        swap(&arr[index_of_min], &arr[i]);
    }
}

void print100ArrayElements(int* v)
{
    for (int i=0; i < 100; i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

int* generateRandomArray(int size){
    int* arr = new int[size];
    for(int i = 0; i < size; i++){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distribution(0, size*10); // define the range

        arr[i] = distribution(eng);
    }
    return arr;
}

//passed as argument to testSort(...) in order to fit "void (*sort)(int* arr, int size)" pattern
void quickSort(int arr[], int size) {
    quickSort(arr, 0, size-1);
}

//passed as argument to testSort(...) in order to fit "void (*sort)(int* arr, int size)" pattern
void mergeSort(int arr[], int size){
    mergeSort(arr, 0, size-1);
}

void testSort(void (*sort)(int*, int), int* arr, int size){

    std::cout << "Before sorting(first 100 elements): "<<std::endl;
    print100ArrayElements(arr);

    unsigned int delta = clock();
    sort(arr, size);
    delta = clock() - delta;

    std::cout << "Sorted array(first 100 elements) : " << std::endl;
    print100ArrayElements(arr);

    std::cout << "Sorting took "<< (float)delta/CLOCKS_PER_SEC <<std::endl;
}

void benchmarkSort(int N, int arr[], void (*sort)(int*, int), const char sortingName[], const char arrayType[]){

    //only the copy will get modified, so the original can be further used while testing another sorting
    int* arrCopy = new int[N];
    std::copy(arr, arr+N, arrCopy);

    std::cout << std::endl << sortingName << " FOR ARRAY OF " << N << " " << arrayType << std::endl;
    testSort(sort, arrCopy, N);
}

void benchmarkMode(){
    std::cout << "\n--------------------------------------- Random array --------------------------------------- \n\n";

    int size = 1000;
    int* arr =  generateRandomArray(size);

    benchmarkSort(size, arr, selectionSort, "SELECTION SORT", "RANDOM ELEMENTS");
    benchmarkSort(size, arr, quickSort, "QUICK SORT", "RANDOM ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "RANDOM ELEMENTS");

    std::cout << "\n-------------------------- \n"<<std::endl;

    size = 10000;
    delete[] arr;
    arr =  generateRandomArray(size);

    benchmarkSort(size, arr, selectionSort, "SELECTION SORT", "RANDOM ELEMENTS");
    benchmarkSort(size, arr, quickSort, "QUICK SORT", "RANDOM ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "RANDOM ELEMENTS");

    std::cout << "\n-------------------------- \n"<<std::endl;

    size = 100000;
    delete[] arr;
    arr =  generateRandomArray(size);

    benchmarkSort(size, arr, quickSort, "QUICK SORT", "RANDOM ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "RANDOM ELEMENTS");

    std::cout << "\n--------------------------------------- Almost sorted array --------------------------------------- \n\n";

    size = 1000;
    delete[] arr;
    arr = new int[size];
    for(int i = 0; i < size; i++){arr[i] = i;}
    swap(&arr[44],&arr[3]);
    swap(&arr[244],&arr[size-3]);
    swap(&arr[7],&arr[793]);

    benchmarkSort(size, arr, selectionSort, "SELECTION SORT", "ALMOST SORTED ELEMENTS");
    benchmarkSort(size, arr, quickSort, "QUICK SORT", "ALMOST SORTED ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "ALMOST SORTED ELEMENTS");

    std::cout << "\n-------------------------- \n"<<std::endl;

    size = 10000;
    delete[] arr;
    arr = new int[size];
    for(int i = 0; i < size; i++){arr[i] = i;}
    swap(&arr[44],&arr[3]);
    swap(&arr[244],&arr[size-3]);
    swap(&arr[7],&arr[793]);

    benchmarkSort(size, arr, selectionSort, "SELECTION SORT", "ALMOST SORTED ELEMENTS");
    benchmarkSort(size, arr, quickSort, "QUICK SORT", "ALMOST SORTED ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "ALMOST SORTED ELEMENTS");

    std::cout << "\n-------------------------- \n"<<std::endl;

    size = 100000;
    delete[] arr;
    arr = new int[size];
    for(int i = 0; i < size; i++){arr[i] = i;}
    swap(&arr[44],&arr[3]);
    swap(&arr[244],&arr[size-3]);
    swap(&arr[7],&arr[793]);

    benchmarkSort(size, arr, quickSort, "QUICK SORT", "ALMOST SORTED ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "ALMOST SORTED ELEMENTS");

    std::cout << "\n--------------------------------------- Reversed array--------------------------------------- \n\n";

    delete[] arr;
    size = 1000;
    arr = new int[size];
    for(int i = 0; i < size; i++){arr[i] = size-i;}

    benchmarkSort(size, arr, selectionSort, "SELECTION SORT", "REVERSE ORDERED ELEMENTS");
    benchmarkSort(size, arr, quickSort, "QUICK SORT", "REVERSE ORDERED ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "REVERSE ORDERED ELEMENTS");

    std::cout << "\n-------------------------- \n"<<std::endl;

    delete[] arr;
    size = 10000;
    arr = new int[size];
    for(int i = 0; i < size; i++){arr[i] = size-i;}

    benchmarkSort(size, arr, selectionSort, "SELECTION SORT", "REVERSE ORDERED ELEMENTS");
    benchmarkSort(size, arr, quickSort, "QUICK SORT", "REVERSE ORDERED ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "REVERSE ORDERED ELEMENTS");

    std::cout << "\n-------------------------- \n"<<std::endl;

    delete[] arr;
    size = 100000;
    arr = new int[size];
    for(int i = 0; i < size; i++){arr[i] = size-i;}

    benchmarkSort(size, arr, quickSort, "QUICK SORT", "REVERSE ORDERED ELEMENTS");
    benchmarkSort(size, arr, mergeSort, "MERGE SORT", "REVERSE ORDERED ELEMENTS");
}

int main() {

    benchmarkMode();

    return 0;
}

void quickSort(int arr[], int start, int end){
    if (start < end)
    {
        int pivot = quickSortPartition(arr, start, end);

        quickSort(arr, start, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

void mergeSort(int arr[], int left, int right){
    if (left < right){
        int middle = left+(right-left)/2;

        // sort left and right half separately
        mergeSort(arr, left, middle);
        mergeSort(arr, middle+1, right);

        mergeSortPartition(arr, left, middle, right);
    }
}

void mergeSortPartition(int arr[], int start, int middle, int end)
{
    int i = 0, j = 0;

    int left_size = middle - start + 1;
    int right_size =  end - middle;
    int left[left_size], right[right_size];

    for (; i < left_size; i++)
        left[i] = arr[start + i];
    for (; j < right_size; j++)
        right[j] = arr[middle + j + 1];

    // compare values in both arrays and put them in ascending order into the initial subarray
    i = j = 0;
    int k = start; // starting index of merged subarray
    while (i < left_size && j < right_size){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // copy the remaining elements if there are any
    while (i < left_size){
        arr[k] = left[i];
        i++; k++;
    }

    while (j < right_size){
        arr[k] = right[j];
        j++; k++;
    }
}

int quickSortPartition (int arr[], int start, int end)
{
    /*
     * Lomuto partition scheme, rightmost pivot
     * takes last element as pivot and places it at its correct position in a subarray sorted in a way that
     * all elements placed before the pivot are smaller and all elements placed after the pivot are bigger
    */

    int pivot = arr[end];
    int new_pivot_position = start - 1; // index of what should be the smallest element

    for (int j = start; j < end; j++)
    {
        if (arr[j] < pivot)
        {
            new_pivot_position++;
             /*
              * new_pivot_position starts to fall behind j when found arr.at(j) such that arr.at(j) >= pivot
              * then this bigger value of arr.at(j) is swapped with next lesser than pivot laying in the interval [j, end]
              * e.g. 1    2(new,j)  9          3     6    7(pivot)
              *      1    2(new)    9(j)       3     6    7(pivot)              9 > 7 => new_pivot_position doesn't get changed
              *      1    2         9(new)     3(j)  6    7(pivot)              3 < 7 => new_pivot_position gets incremented
              *      1    2         3(new)     9(j)  6    7(pivot)              then 3 and 9 get swapped
             */
            if(new_pivot_position!=j)
                swap(&arr[new_pivot_position], &arr[j]);
        }
    }

    new_pivot_position++;
    if(new_pivot_position!=end)
        swap(&arr[new_pivot_position], &arr[end]);

    return new_pivot_position;
}

