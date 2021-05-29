//
// Created by User on 029 29.05.21.
//
#include <exception>
#include "matrix.h"
double Matrix::determinant() {
    if(_rows!=_cols) throw("matrix is ot square");


}

Matrix Matrix::subMatrix(int p,int q) {
    int i=0;
    int j=0;
    double **temp = new double *[this->_rows];
    for(int i = 0; i < _rows; ++i)
        temp[i] = new double [_cols];
    for (int row = 0; row < _rows; row++) {
        for (int col = 0; col < _cols; col++) {

            if (row != p && col != q) {
                temp[i][j++] = _data[row][col];
                if (j == _cols - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }



    return ;
}

Matrix::Matrix(double **data,double* free_var,int rows, int cols):_cols(cols),_rows(rows){
    {
        _data=data;
        _free_var=free_var;
    }
}


