#ifndef STRATEGY_H
#define STRATEGY_H
#include "Solve.h"
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
     static int solvingMethod(Solve* solvePrt, int*& arr, int size);
     static int solvingMethod(Strategies strategy, int*& arr, int size);
};

#endif // STRATEGY_H
