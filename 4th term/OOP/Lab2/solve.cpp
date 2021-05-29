#include "solve.h"

double* Solve::startMethod (double** matrix, int rows, int cols){
    this->_matrix = matrix;
    this->_rows = rows;
    this->_cols = cols;

    double* result = solvingMethod();
    return result;
}

double* Method1::solvingMethod(){

    return nullptr;
}
