#include "factory.h"
#include "strategy.h"

Solve* Factory::createSolveObject(int methodNumber){
    switch(methodNumber){
        case Strategy::Strategies::Method1:
            return new Method1();
        default:
            return NULL;
    }
}
