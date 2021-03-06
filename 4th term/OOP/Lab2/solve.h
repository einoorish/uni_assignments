#ifndef METHOD_H
#define METHOD_H
#include "matrix.h"
#include <cmath>
#include "iostream"

class Solve
{
    protected:
        Matrix* _matrix;
        virtual double* solvingMethod() = 0;
    public:
        double* startMethod(Matrix& matrix);
};

class Kramer:public Solve{
public:
    double* solvingMethod() override;
    Kramer(): Solve(){_matrix = new Matrix();};
};

class Jacobi:public Solve{
public:
    double* solvingMethod() override;
    Jacobi(): Solve(){_matrix = new Matrix();};
};

class Gauss:public Solve{
public:
    double* solvingMethod() override;
    Gauss(): Solve(){_matrix = new Matrix();};
};

#endif // METHOD_H
