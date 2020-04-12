#include "CountingSort.h"

int getIndex(std::string units){
    for(int i = 0; i<UNITS_ARR_SIZE; i++)
        if(units == UNITS_OF_MEASUREMENT[i]) return i;

}

//Sorts only by UNITS field
void countingSort(Item* arr, int N){

    Item* result = new Item[N];
    int count[UNITS_ARR_SIZE] = {0}; // range is 4: 0 - "kilograms", 1 - "packages", 2 - "pieces", 3 - "liters"

    // count occurrences of each unit
    for(int i = 0; i < N; i++)
        ++count[getIndex(arr[i].getUnits())];

    // add occurrences count of previous units to count[i] so it would contain starting position of current unit
    for (int i = 1; i <= UNITS_ARR_SIZE; ++i)
        count[i] += count[i-1];

    int index = 0;

    for (int i = N-1; i >= 0; i--){
        index = getIndex(arr[i].getUnits());
        result[count[index]-1] = arr[i];
        count[index]--;
    }

    // copy the result to arr
    for (int i = 0; i < N; i++)
        arr[i] = result[i];

    delete []result;
}
