#include "solve.h"
#include<QDebug>
double* Solve::startMethod (Matrix& matrix){
    this->_matrix = &matrix;
    double* result = solvingMethod();
    return result;
}

double* Kramer::solvingMethod(){
    if (this->_matrix->determinant()==0)
        return nullptr;
    auto *ans= new double[_matrix->getCols()];

    std::cout << "\nMatrix--------------------- " << std::endl;

    for(int j = 0; j < 4; j++){
        for(int k = 0; k < 4; k++)
            std::cout << _matrix->_data[j][k] << " ";
        std::cout << std::endl;
    }
    std::cout << "\n---------------------\n Temp: " << std::endl;

    Matrix temp=Matrix(_matrix->_data, _matrix->_free_var, _matrix->getRows(), _matrix->getCols());
    for(int i=0;i<_matrix->getRows();i++){
        for(int j = 0; j < _matrix->getCols(); j++){
            temp._data[j][i]=_matrix->_free_var[j];
        }

        std::cout << "\n---------- " << std::endl;
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++)
                std::cout << temp._data[j][k] << " ";
            std::cout << std::endl;
        }

        ans[i]=temp.determinant()/_matrix->determinant();

        for(int j = 0; j < _matrix->getCols(); j++){
            temp._data[j][i]=_matrix->_data[j][i];
        }
    }

    return ans;
}
