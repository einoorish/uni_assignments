#pragma once

#include "BenchmarkMode.h"
#include "DemoMode.h"

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

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl << std::endl;
}

int main() {

    int command;
    std::cout << "1 - demo mode\n2 - benchmark mode" << std::endl;
    std::cin >> command;

    if(command == 1) demo::demoMode();
    else if (command == 2) benchmark::benchmarkMode();
    else return 0;

    main();

    return 0;
}
