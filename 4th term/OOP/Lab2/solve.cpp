#include "solve.h"

double* Solve::startMethod (Matrix matrix){
    this->_matrix = matrix;


    double* result = solvingMethod();
    return result;
}

double* Kramer::solvingMethod(){

    return nullptr;
}
