#include "factory.h"
#include "strategy.h"

Solve* Factory::createSolveObject(int methodNumber){
    switch(methodNumber){
        case Strategy::Kramer:
            return new Kramer();
        default:
            return NULL;
    }
}
