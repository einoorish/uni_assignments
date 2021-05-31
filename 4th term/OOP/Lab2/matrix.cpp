#include <algorithm>
#include <exception>
#include "matrix.h"
double Matrix::determinant() {
    if(_rows!=_cols) throw("matrix is ot square");

    double determinant = 0;
    if (_rows == 1) {
        return _data[0][0];
    }
    if (_rows == 2) {
        return (_data[0][0] * _data[1][1]) - (_data[0][1] * _data[1][0]);
    }
    double **temp_data = new double *[this->_rows];
    for(int i = 0; i < _rows; ++i)
        temp_data[i] = new double [_cols];
    Matrix temp(temp_data, {0},_rows-1,_cols-1);
    double sign = 1;
     for (int i = 0; i < _rows; i++) {
            temp = subMatrix( 0, i);
            determinant += sign * _data[0][i] * temp.determinant();
            sign = -sign;
     }
        return determinant;
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
    return Matrix(temp,_free_var,_rows-1,_cols-1 );
}

Matrix::Matrix(double **data, double* free_var,int rows, int cols){
   _cols=cols;
    _rows=rows;
    _data = new double*[rows];
    for(int i =0 ; i < rows; i++){
        _data[i]=new double[cols];
        for(int j = 0; j < cols; j++){
            _data[i][j] = data[i][j];
        }
    }
//    std::copy(&data[0][0], &data[0][0]+rows*cols,&_data[0][0]);
    //_data=data;
    _free_var=free_var;
}

int Matrix::getRows() const{
    return _rows;
}int Matrix::getCols() const{
    return _cols;
}




