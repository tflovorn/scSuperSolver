#include "RootFinder.hh"

RootFinder::RootFinder(double (*function)(), double* variable, 
    const double tolerance) : myFn(function), myVar(variable), myTol(tolerance)
{ }

double RootFinder::getVar() {
    return *myVar;
}

double RootFinder::getFnValue() {
    return myFn();
}
