#ifndef __MFTS_ROOT_FINDER_H
#define __MFTS_ROOT_FINDER_H

// -- one-dimensional --

#define RF_MAX_ITER 1000

class RootData {
public:
    RootData(bool cvg, double rt, double fnv);
    bool converged;
    double root, fnvalue;
};

class RootFinder {
public:
    // Constructor.  Only saves parameters.
    RootFinder(double (* const helper)(double, void*), void * const params, 
               const double guess, const double min, const double max, 
               const double tolerance);
    // Encapsulates the heavy lifting of root-finding.
    // If a root is found, returns true.  Otherwise returns false.
    const RootData& findRoot();
private:
    // Function to find root of.
    double (* const myHelper)(double, void *);
    // Extra parameters to pass in to function
    void * const myParams;
    // Starting value for the variable.
    const double myGuess;
    // Minimum and maximum values to try for the variable.
    const double myMin, myMax;
    // If findRoot returns true, then abs(myFn()) <= myTolerance.
    const double myTolerance;
};

#endif
