#include "strategy.h"
#include "factory.h"

std::map<Strategy::Strategies, Solve*> solvePtr = initMethods();

int Strategy::solvingMethod(Solve *solvePtr, int *&arr, int size){
    if(solvePtr == nullptr){
        initMethods();
    }

    int result = solvePtr->startMethod(arr, size);
    return result;
}

int Strategy::solvingMethod(Strategies strategy, int *&arr, int size){

    if(solvePtr.count(strategy)){
        int result = solvePtr[strategy]->startMethod(arr, size);
        return result;
    }
}

void Strategy::initMethods(){
    solvePtr.insert(std::pair<Strategies, Solve*>(Method1, Factory::createSolveObject(Method1))));
}
