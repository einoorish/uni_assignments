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
    int i, j, k = 1;
    double sum;
    for (i = 0; i < _matrix->getCols(); i++) {
        sum = 0;
        for (j = 0; j < _matrix->getCols(); j++)
            sum += fabs(_matrix->_data[i][j]);
        sum -= fabs(_matrix->_data[i][i]);
        if (sum > fabs(_matrix->_data[i][i]))
            throw("Matrix is not Diagonally dominant");
    }
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

double* Gauss::solvingMethod(){
    double *ans, max;
    int k, index;
    const double eps = 0.00001;
    ans = new double[_matrix->getCols()];
    k = 0;
    while (k < _matrix->getCols())
    {
        max = fabs(_matrix->_data[k][k]);
        index = k;
        for (int i = k + 1; i < _matrix->getCols(); i++)
        {
            if (fabs(_matrix->_data[i][k]) > max)
            {
                max = fabs(_matrix->_data[i][k]);
                index = i;
            }
        }

        if (max < eps)
        {
            return nullptr;
        }
        for (int j = 0; j < _matrix->getCols(); j++)
        {
            double temp = _matrix->_data[k][j];
            _matrix->_data[k][j] = _matrix->_data[index][j];
            _matrix->_data[index][j] = temp;
        }
        double temp = _matrix->_free_var[k];
        _matrix->_free_var[k] = _matrix->_free_var[index];
        _matrix->_free_var[index] = temp;

        for (int i = k; i < _matrix->getCols(); i++)
        {
            double temp = _matrix->_data[i][k];
            if (fabs(temp) < eps) continue;
            for (int j = 0; j < _matrix->getCols(); j++)
                _matrix->_data[i][j] = _matrix->_data[i][j] / temp;
            _matrix->_free_var[i] = _matrix->_free_var[i] / temp;
            if (i == k)  continue;
            for (int j = 0; j < _matrix->getCols(); j++)
                _matrix->_data[i][j] = _matrix->_data[i][j] - _matrix->_data[k][j];
            _matrix->_free_var[i] = _matrix->_free_var[i] - _matrix->_free_var[k];
        }
        k++;
    }

    for (k = _matrix->getCols() - 1; k >= 0; k--)
    {
        ans[k] = _matrix->_free_var[k];
        for (int i = 0; i < k; i++)
            _matrix->_free_var[i] = _matrix->_free_var[i] - _matrix->_data[i][k] * ans[k];
    }
    return ans;
}
