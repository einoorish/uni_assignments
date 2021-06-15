#include "factory.h"
#include "strategy.h"

Solve* Factory::createSolveObject(int methodNumber){
    switch(methodNumber){
        case Strategy::Kramer:
            return new Kramer();
        case Strategy::Jacobi:
            return new Jacobi();
        case Strategy::Gauss:
            return new Gauss();
        default:
            return NULL;
    }
}
