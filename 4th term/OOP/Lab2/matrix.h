//
// Created by User on 029 29.05.21.
//

#ifndef UNI_ASSIGNMENTS_MATRIX_H
#define UNI_ASSIGNMENTS_MATRIX_H
class Matrix{
protected:

    int _rows;
    int _cols;
public:
    double* _free_var;
    double** _data;
    Matrix(double** data, double* free_var,  int rows, int cols);
    double determinant();
    Matrix subMatrix(int p,int q);
   /*const Matrix& operator=(Matrix& matr){
        Matrix temp(matr._data,matr._free_var,matr._rows,matr._cols);

        return temp;
    };*/
};
#endif //UNI_ASSIGNMENTS_MATRIX_H
