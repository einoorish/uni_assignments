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

    Matrix temp=Matrix(_matrix->_data, _matrix->_free_var, _matrix->getRows(), _matrix->getCols());
    for(int i=0;i<_matrix->getRows();i++){
        for(int j = 0; j < _matrix->getCols(); j++){
            temp._data[j][i]=_matrix->_free_var[j];
        }
        ans[i]=temp.determinant()/_matrix->determinant();

        for(int j = 0; j < _matrix->getCols(); j++){
            temp._data[j][i]=_matrix->_data[j][i];
        }
    }

    return ans;
}
double* Jacobi::solvingMethod() {
    if (this->_matrix->determinant() == 0)
        return nullptr;
    auto *ans = new double[_matrix->getCols()];



    return ans;
}
double* Zeidel::solvingMethod() {
    if (this->_matrix->determinant() == 0)
        return nullptr;
    auto *ans = new double[_matrix->getCols()];



    return ans;
}