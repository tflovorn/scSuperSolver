#ifndef __MFTS_STATE_H
#define __MFTS_STATE_H

#include "Environment.h"

class State {
public:
    // Constructor. Needs to examine envIn to set member variables.
    State(const Environment& envIn);
    // Destructor.  Not responsible for destroying env.
    ~State();
    // Drive calculations needed to make this State consistent
    // with the given Environment.  Return false if unable to converge.
    bool makeSelfConsistent();
    // Return true is the errors in all self-consistent equations are within
    // their tolerances, false otherwise.
    bool checkSelfConsistent() const;
    // Return true if the error in the associated S-C equation is within
    // tolerance, false otherwise.
    bool checkD1() const;
    bool checkMu() const;
    bool checkF0() const;
    // Return fractional error in the associated S-C equation.
    double errorD1() const;
    double errorMu() const;
    double errorF0() const;
    // Simple getters.
    double getD1() const;
    double getMu() const;
    double getF0() const;
    double getEpsilonMin() const;
    // Minimizer needs to be a friend to do its dirty work.
    friend class Minimizer;
    // Our Environment, containing all the configuration info we need.
    const Environment& env;
private:
    // Self-consistent variables.
    double d1, mu, f0;
    // Minimum of Spectrum::epsilonBar() on the BZone.
    // The correct value for this depends on env and d1.
    double epsilonMin;
    // Set epsilonMin to the appropriate value.
    // -- Need to call this after changing D1! --
    double setEpsilonMin();
    // Set the variable to the value which minimizes the error in the
    // associated self-consistent equation. Return value found.
    // Note: d1 and mu equations are coupled, so they must be iterated 
    // together to find a pair of values that satisfies both equations.
    double fixD1();
    double fixMu();
    double fixF0();
};

#endif
