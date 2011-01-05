/*
  Copyright (c) 2011 Timothy Lovorn

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

#ifndef __SCSS_CRIT_TEMP_SPECTRUM_H
#define __SCSS_CRIT_TEMP_SPECTRUM_H

#include <cmath>

#include "CritTempState.hh"

struct PiOutput {
    double xx, xy, yy;
};

class CritTempSpectrum {
public:
    // One-hole spectrum to be used, minimum at 0
    static double epsilon(const CritTempState& st, double kx, double ky);
    // One-hole spectrum unmodified from theory
    static double epsilonBar(const CritTempState& st, double kx, double ky);
    // One-hole energy, epsilon - mu
    static double xi(const CritTempState& st, double kx, double ky);
    // Fermi distribution function (for T>0)
    static double fermi(const CritTempState& st, double energy);
    // Bose distribution function (T>0)
    static double bose(const CritTempState& st, double energy);
    // term to be summed to calculate x1 (x2 = x - x1)
    static double innerX1(const CritTempState& st, double kx, double ky);
    // used to calculate Re Pi (xx, xy, yy)
    // TODO
    static PiOutput innerPi(const CritTempState& st, double omega, double kx, 
                            double ky, double qx, double qy);
    // term to be summed to calculate rhs of associated S-C equation
    static double innerD1(const CritTempState& st, double kx, double ky);
    static double innerMu(const CritTempState& st, double kx, double ky);
    // TODO
    static double innerBp(const CritTempState& st, double kx, double ky);
};

#endif
