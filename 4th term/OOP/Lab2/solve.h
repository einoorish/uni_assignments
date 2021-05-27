#ifndef METHOD_H
#define METHOD_H

class Solve
{
    protected:
        double** _matrix;
        int _rows;
        int _cols;

        virtual double* solvingMethod() = 0;
    public:
        double* startMethod(double** matrix, int rows, int cols);
};

class Method1:public Solve{
public:
    double* solvingMethod() override;
};

#endif // METHOD_H
