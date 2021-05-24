#ifndef METHOD_H
#define METHOD_H


class Solve
{
    protected:
        int *_array;
        int _arraySize;

        virtual int solvingMethod() = 0;
    public:
        int startMethod(int* array, int size);
};

class Method1:public Solve{
public:
    int solvingMethod() override;
};

#endif // METHOD_H
