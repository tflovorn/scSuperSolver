/****************************************************************************
 * Copyright (C) 2010 Timothy Lovorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef __MFTS_ROOT_FINDER_H
#define __MFTS_ROOT_FINDER_H

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
