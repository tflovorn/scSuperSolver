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

#ifndef __SCSS__BZONE_H
#define __SCSS__BZONE_H

#include <cmath>
#include <cfloat>

#include "BaseState.hh"
#include "ZeroTempState.hh"

class BZone {
public:
    template <class SpecializedState>
    static double average(const BaseState& stBase, 
        const SpecializedState& stSpec, 
        double (*innerFunc)(const SpecializedState&, double, double));

    template <class SpecializedState>
    static double minimum(const BaseState& stBase, 
        const SpecializedState& stSpec, 
        double (*innerFunc)(const SpecializedState&, double, double));
};

// Would be nice to have a single function handle transforming one BZone point
// into another instead of duplicating the traversal
// OR just specify accumulator function (val = accum(val, thisPointVal))
template <class SpecializedState>
double BZone::minimum(const BaseState& stBase, 
        const SpecializedState& stSpec, 
        double (*innerFunc)(const SpecializedState&, double, double)) {
    double kx = -M_PI, ky = -M_PI, min = DBL_MAX, val;
    int N = stBase.env.gridLen;
    double step = 2 * M_PI / N;
    while (ky < M_PI) {
        while (kx < M_PI) {
            val = innerFunc(stSpec, kx, ky);
            if (val < min) {
                min = val;
            }      
            kx += step;      
        }
        ky += step;
        kx = -M_PI;
    }
    return min;
}

template <class SpecializedState>
double BZone::average(const BaseState& stBase, 
        const SpecializedState& stSpec, 
        double (*innerFunc)(const SpecializedState&, double, double)) {
    double kx = -M_PI, ky = -M_PI, min = DBL_MAX, sum = 0.0;
    int N = stBase.env.gridLen;
    double step = 2 * M_PI / N;
    while (ky < M_PI) {
        while (kx < M_PI) {
            sum += innerFunc(stSpec, kx, ky);
            kx += step;      
        }
        ky += step;
        kx = -M_PI;
    }
    return sum / (N * N);
}

#endif
