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

#ifndef __SCSS_ROOT_FINDER_H
#define __SCSS_ROOT_FINDER_H

#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

// -- one-dimensional --

#define RF_MAX_ITER 1024
#define RF_BRACKET_STEPS 32

class RootData {
public:
    RootData(bool cvg, double rt, double fnv);
    bool converged;
    double root, fnvalue;
};

class BracketData {
public:
    BracketData(bool _success, double _left, double _right, 
                double _fnleft, double _fnright);
    bool success;
    double left, right, fnleft, fnright;
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
    const BracketData& bracket();
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
