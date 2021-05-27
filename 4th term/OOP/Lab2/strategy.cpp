#include "strategy.h"
#include "factory.h"

std::map<Strategy::Strategies, Solve*> Strategy::solvePtr;
double* Strategy::solvingMethod(Solve *solvePtr, double**matrix, int rows, int cols){
    if(solvePtr == nullptr){
        initMethods();
    }

    double* result = solvePtr->startMethod(matrix, rows, cols);
    return result;
}

double* Strategy::solvingMethod(Strategies strategy, double** matrix, int rows, int cols){
    if(solvePtr.empty()){
        initMethods();
    }

    if(solvePtr.count(strategy)){
        double* result = solvePtr[strategy]->startMethod(matrix, rows, cols);
        return result;
    }
    return nullptr;
}

void Strategy::initMethods(){
    solvePtr.insert(std::pair<Strategies, Solve*>(Method1, Factory::createSolveObject(Method1)));
}
