#include <iostream>

#include "RootFinder.hh"

double test_root_linear(double x, void *params) {
    return 1 - x;
}

int main(int argc, char *argv[]) {
    RootFinder rf(&test_root_linear, NULL, 0.0, -10.0, 10.0, 1e-6);
    rf.findRoot();

    return 0;
}
