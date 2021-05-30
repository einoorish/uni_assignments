#include "strategy.h"
#include "factory.h"

std::map<Strategy::Strategies, Solve*> Strategy::solvePtr;
double* Strategy::solvingMethod(Solve *solvePtr, Matrix matrix){
    if(solvePtr == nullptr){
        initMethods();
    }

    double* result = solvePtr->startMethod(matrix);
    return result;
}

double* Strategy::solvingMethod(Strategies strategy, Matrix matrix){
    if(solvePtr.empty()){
        initMethods();
    }

    if(solvePtr.count(strategy)){
        double* result = solvePtr[strategy]->startMethod(matrix);
        return result;
    }
    return nullptr;
}

void Strategy::initMethods(){
    solvePtr.insert(std::pair<Strategies, Solve*>(Kramer, Factory::createSolveObject(Kramer)));
}
