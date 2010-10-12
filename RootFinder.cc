#include "RootFinder.hh"

RootFinder::RootFinder(double (* const helper)(double, void *), 
    const double tolerance) : myHelper(helper), myTolerance(tolerance) {}

double RootFinder::findRoot() {
    return *myVar;
}
