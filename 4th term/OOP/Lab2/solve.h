#ifndef METHOD_H
#define METHOD_H
#include "matrix.h"
class Solve
{
    protected:
        Matrix _matrix;

        virtual double* solvingMethod() = 0;
    public:
        double* startMethod(Matrix matrix);
};

class Kramer:public Solve{
public:
    double* solvingMethod() override;
};

#endif // METHOD_H
