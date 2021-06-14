#ifndef STRATEGY_H
#define STRATEGY_H
#include "solve.h"
#include "map"

class Strategy
{
public:
     enum Strategies{
         Kramer,
         Jacobi,
         Zeidel
     };
private:
     static std::map<Strategies, Solve*> solvePtr;
     static void initMethods();
public:
     static double* solvingMethod(Solve* solvePrt, Matrix matrix);
     static double* solvingMethod(Strategies strategy, Matrix matrix);
};

#endif // STRATEGY_H
