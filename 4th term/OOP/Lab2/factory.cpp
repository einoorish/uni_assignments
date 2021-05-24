#include "factory.h"
#include "strategy.h"

Solve* Factory::CreateSolveObject(int methodNumber){
    switch(methodNumber){
        case Strategy::Method1:
            return new Method1();
        default:
            return NULL;
    }
}
