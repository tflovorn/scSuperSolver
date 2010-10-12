#ifndef __MFTS_ROOT_FINDER_H
#define __MFTS_ROOT_FINDER_H

// -- one-dimensional --
class RootFinder {
public:
    // Constructor.  Only saves parameters.
    RootFinder(double (*helper)(double, void*), const double tolerance);
    // Encapsulates the heavy lifting of root-finding.
    // If a root is found, returns true.  Otherwise returns false.
    bool findRoot();
private:
    // Function to find root of.
    double (* const myHelper)(double, void *);
    // If findRoot returns true, then abs(myFn()) <= myTolerance.
    const double myTolerance;
};

#endif
