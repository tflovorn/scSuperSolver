#ifndef __MFTS_MINIMIZER_H
#define __MFTS_MINIMIZER_H

// -- one-dimensional --
class RootFinder {
public:
    // Constructor.  Only saves parameters.
    RootFinder(double (*function)(), double* variable, const double tolerance);
    // Destructor.  Doesn't delete anything.
    ~RootFinder();
    // Encapsulates the heavy lifting of root-finding.
    // If a root is found, returns true.  Otherwise returns false.
    bool findRoot();
    // Returns value of myVar.
    double getVar();
    // Returns result of calling myFn().
    double getAccuracy();
private:
    // Function to find root of.
    double (*myFn)();
    // Find root by adjusting this variable.
    double *myVar;
    // If findRoot returns true, then abs(myFn()) <= myTol.
    const double myTol;
};

#endif
