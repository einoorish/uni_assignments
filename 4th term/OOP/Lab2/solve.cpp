#include "solve.h"

int Solve::startMethod (int *array, int size){
    this->_array = array;
    this->_arraySize = size;
    int result = solvingMethod();

    return result;
}

int Method1::solvingMethod(){
    return 1;
}
