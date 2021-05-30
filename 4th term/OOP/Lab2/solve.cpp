#include "solve.h"

double* Solve::startMethod (Matrix matrix){
    this->_matrix = matrix;


    double* result = solvingMethod();
    return result;
}

double* Kramer::solvingMethod(){
if (_matrix.determinant()==0)
    return nullptr;
auto *ans= new double[_matrix.getCols()];

Matrix temp=_matrix;
for(int i=0;i<_matrix.getCols();i++){
    Matrix temp=_matrix;
    temp._data[i]=_matrix._free_var;
    ans[i]=temp.determinant()/_matrix.determinant();
}

return ans;
}
