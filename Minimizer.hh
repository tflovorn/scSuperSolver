#ifndef __MFTS_MINIMIZER_H
#define __MFTS_MINIMIZER_H

// -- one-dimensional --

#define MINIMIZER_MAX_ITER 1000

class MinimumData {
public:
    MinimumData(bool cvg, double min, double fnv);
    bool converged;
    double x_min, fnvalue;
};

class Minimizer {
public:
    // Constructor.  Only saves parameters.
    Minimizer(double (* const helper)(double, void*), void * const params, 
              const double guess, const double range_min, 
              const double range_max, const double tolerance);
    // Encapsulates the heavy lifting of minimization.
    // If a minimum is found, returns true.  Otherwise returns false.
    const MinimumData& findMinimum();
private:
    // Function to find minimum of.
    double (* const myHelper)(double, void *);
    // Extra parameters to pass in to function
    void * const myParams;
    // Starting value for the variable.
    const double myGuess;
    // Minimum and maximum values to try for the variable.
    const double myRangeMin, myRangeMax;
    // If findMinimum returns true, then abs(myFn()) <= myTolerance.
    const double myTolerance;
};

#endif
