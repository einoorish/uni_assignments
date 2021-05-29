#ifndef METHOD_H
#define METHOD_H
#iclude <matrix>
class Solve
{
    protected:
        Matrix _matrix;

        virtual double* solvingMethod() = 0;
    public:
        double* startMethod(double** matrix, int rows, int cols);
};

class Method1:public Solve{
public:
    double* solvingMethod() override;
};

#endif // METHOD_H
