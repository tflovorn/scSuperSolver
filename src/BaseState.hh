/*
  Copyright (c) 2010 Timothy Lovorn

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef __SCSS_BASE_STATE_H
#define __SCSS_BASE_STATE_H

#include <cmath>
#include <iostream>

#include "BaseEnvironment.hh"

class BaseState {
public:
    // Constructor needs to examine envIn to set member variables.
    BaseState(const BaseEnvironment& envIn);
    // Drive calculations needed to make this State consistent
    // with the given Environment.  Return false if unable to converge.
    virtual bool makeSelfConsistent() = 0;
    // Return true is the errors in all self-consistent equations are within
    // their tolerances, false otherwise.
    virtual bool checkSelfConsistent() const = 0;
    // Return true if the error in the associated S-C equation is within
    // tolerance, false otherwise.
    virtual bool checkD1() const;
    virtual bool checkMu() const;
    // Return absolute error in the associated S-C equation.
    virtual double absErrorD1() const = 0;
    virtual double absErrorMu() const = 0;
    // Relative error
    virtual double relErrorD1() const = 0;
    virtual double relErrorMu() const = 0;
    // Simple getters.
    double getD1() const;
    double getMu() const;
    double getEpsilonMin() const;
    // Output what state is now.
    virtual void logState() const = 0;
    // RootFinder needs to be a friend to do its dirty work.
    friend class RootFinder;
    // Our Environment, containing all the configuration info we need.
    const BaseEnvironment& env;
protected:
    // Self-consistent variables.
    double d1, mu;
    // Minimum of Spectrum::epsilonBar() on the BZone.
    // The correct value for this depends on env and d1.
    double epsilonMin;
    // Set epsilonMin to the appropriate value.
    // -- Need to call this after changing D1! --
    virtual double setEpsilonMin() = 0;
    // Set the variable to the value which minimizes the error in the
    // associated self-consistent equation. Return value found.
    // Note: d1 and mu equations are coupled, so they must be iterated 
    // together to find a pair of values that satisfies both equations.
    virtual bool fixD1() = 0;
    virtual bool fixMu() = 0;
};

#endif
