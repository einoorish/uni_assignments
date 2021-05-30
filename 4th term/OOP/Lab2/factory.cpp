#include "factory.h"
#include "strategy.h"

Solve* Factory::createSolveObject(int methodNumber){
    switch(methodNumber){
        case Strategy::Strategies::Kramer:
            return new Method1();
        default:
            return NULL;
    }
}
