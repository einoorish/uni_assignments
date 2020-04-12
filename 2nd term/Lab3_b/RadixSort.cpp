#include "RadixSort.h"


//Sorts only by EXPIRATION_PERIOD field
void radixSort(Item* arr, int N) {

    int max = 499; // expiration period is always less than 500

    for (int currentRadix = 1; max / currentRadix > 0; currentRadix *= 10) {
        //same as counting sort:

        Item *output = new Item[N];
        int count[10] = { 0 };

        for (int i = 0; i < N; i++)
            ++count[((int)arr[i].getExpirationPeriod() / currentRadix) % 10];

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        int index = 0;

        for (int i = N - 1; i >= 0; i--){
            index = ((int)arr[i].getExpirationPeriod() / currentRadix) % 10; // count index == digit at the current radix
            output[count[index] - 1] = arr[i];
            count[index]--;
        }

        for (int i = 0; i < N; i++)
            arr[i] = output[i];
    }
}
