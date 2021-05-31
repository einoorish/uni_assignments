#include "solve.h"

double* Solve::startMethod (Matrix& matrix){
    this->_matrix = &matrix;

    double* result = solvingMethod();
    return result;
}

double* Kramer::solvingMethod(){
    if (this->_matrix->determinant()==0)
        return nullptr;
    auto *ans= new double[_matrix->getCols()];


    Matrix* temp=_matrix;
    for(int i=0;i<_matrix->getCols();i++){
        temp=_matrix;
        temp->_data[i]=_matrix->_free_var;
        double a = temp->determinant();
        double b = _matrix->determinant();
        ans[i]=temp->determinant()/_matrix->determinant();

    }

    return ans;
}
