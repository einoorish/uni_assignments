#include "solve.h"
#include <cmath>
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
    for(int i=0;i<_matrix->getCols();i++) ans[i]=1;
    double eps=0.01;
    double* temp = new double[_matrix->getCols()];
    double norm;
    do {
        for (int i = 0; i < _matrix->getCols(); i++) {
            temp[i] = _matrix->_free_var[i];
            for (int g = 0; g < _matrix->getCols(); g++) {
                if (i != g)
                    temp[i] -= _matrix->_data[i][g] * ans[g];
            }
            temp[i] /= _matrix->_data[i][i];
        }
        norm = fabs(ans[0] - temp[0]);
        for (int h = 0; h < _matrix->getCols(); h++) {
            if (fabs(ans[h] - temp[h]) > norm)
                norm = fabs(ans[h] - temp[h]);
            ans[h] = temp[h];
        }
    } while (norm > eps);
    return ans;
}
double* Zeidel::solvingMethod() {
    if (this->_matrix->determinant() == 0)
        return nullptr;
    auto *ans = new double[_matrix->getCols()];
for(int i=0;i<_matrix->getCols();i++) ans[i]=1;



    return ans;
}