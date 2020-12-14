#include <iostream>
using namespace std;

void bubbleSort(int arr[],int n);//бульбашкове сортування
void insertionSort(int arr[], int size);//сортування вставками
void selectionSort(int arr[], int n);//вибіркове сортування
void radixSort(int* arr, int n);//розрядне сортування
void quickSort(int arr[], int size, int left, int right);//швидке сортування
bool outputQS = true;

int main(){
    int size;
    cin >> size;

    int* a = new int[size];

    for (int i = 0; i < size; i++) {
        cin >> a[i];
    }
    //bubbleSort(a, size); cout << endl;
    //selectionSort(a, size); cout << endl;
    //insertionSort(a, size); cout << endl;
    //radixSort(a, size); cout << endl;
    //quickSort(a, size, 0, size-1); cout << endl;

}
void bubbleSort(int a[],int n){
    bool isSorted = false;
    while(!isSorted)
    {
        isSorted = true;
        for(int j=0;j<n-1;j++)
        {
            if(a[j]>a[j+1])
            {
                int temp;
                isSorted = false;
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
}

void selectionSort(int a[], int n) {
    cout << "selection sort says: ";
    int temp, maxIndex;
    for (int i = 0; i < n - 1; i++)
    {
        temp = a[i];
        maxIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[maxIndex])
                maxIndex = j;//found next max
        }

        if (maxIndex != i)//swap if max is not this
        {
            a[i] = a[maxIndex];
            a[maxIndex] = temp;
        }
    }

    for (int i = 0; i < n; i++) cout << a[i] << " ";
}

void insertionSort(int a[], int size) {

    cout << "insertion sort says: ";

    for (int i = 0; i < size; i++) {
        int temp = a[i];

        int j =i-1;
        while(j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];//swap
            j--;
        }
        a[j + 1] = temp;
    }


    for (int i = 0; i < size; i++) {
        cout << a[i] << ' ';
    }
}

int getMax(int a[], int n)
{
    int max = a[0];
    for (int x = 1; x < n; x++)
        if (a[x] > max)
            max = a[x];
    return max;
}

void radixSort(int* arr, int n) {

    cout << "radix sort says: ";

    int max = getMax(arr, n);

    for (int currentRadix = 1; max / currentRadix > 0; currentRadix *= 10) { //currentRadix = 10 ^ i, i is current digit number
        int *output = new int[n];
        int i, count[10] = { 0 };

        //store count of occurrences in count[]: index is digit, value is number of occurences of a digit
        for (i = 0; i < n; i++)
            count[(arr[i] / currentRadix) % 10]++;

        //change count[i] so that count[i] now contains actual position of this digit in output[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        //building the output array
        for (i = n - 1; i >= 0; i--){
            //count[(arr[i] / currentRadix) % 10] is for getting the digit at position of the current radix(count index)
            //count's value will tell the position of arr[i] in the output array,
            //...-1 since index of first occurency(1) should be 0
            output[count[(arr[i] / currentRadix) % 10] - 1] = arr[i];
            count[(arr[i] / currentRadix) % 10]--;//-one occurency
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i]; // output is arr sorted by current radix
    }

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

void quickSort(int arr[], int size, int left, int right) {

    int i = left, j = right;
    int tmp;

    int pivot = arr[(left + right) / 2];

    //partition
    while (i <= j) {
        while (arr[i] < pivot)i++;
        while (arr[j] > pivot)j--;

        if (i <= j) {//swap
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    //recursion
    if (left < j)
        quickSort(arr, size, left, j);

    if (i < right)
        quickSort(arr, size, i, right);

    if (outputQS) {
        outputQS = false;
        cout << "quick sort says: ";
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
    }
}