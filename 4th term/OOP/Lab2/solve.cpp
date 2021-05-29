#include "solve.h"

double* Solve::startMethod (Matrix matrix){
    this->_matrix = matrix;


    double* result = solvingMethod();
    return result;
}

double* Method1::solvingMethod(){

    return nullptr;
}
