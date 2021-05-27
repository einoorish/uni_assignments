#ifndef STRATEGY_H
#define STRATEGY_H
#include "solve.h"
#include "map"

class Strategy
{
public:
     enum Strategies{
         Method1
     };
private:
     static std::map<Strategies, Solve*> solvePtr;
     static void initMethods();
public:
     static double* solvingMethod(Solve* solvePrt, double** matrix, int rows, int cols);
     static double* solvingMethod(Strategies strategy, double** matrix, int rows, int cols);
};

#endif // STRATEGY_H
