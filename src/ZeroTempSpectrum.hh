/*
  Copyright (c) 2010, 2011 Timothy Lovorn

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

#ifndef __SCSS_ZERO_TEMP_SPECTRUM_H
#define __SCSS_ZERO_TEMP_SPECTRUM_H

#include <cmath>

#include "ZeroTempState.hh"

class ZeroTempSpectrum {
public:
    ZeroTempSpectrum(const ZeroTempState& _st);
    // Superconducting gap
    double delta(double kx, double ky) const;
    // Energy of a superconducting pair
    double pairEnergy(double kx, double ky) const;
    // Fermi distribution function (for T=0)
    double fermi(double energy) const;
    // term to be summed to calculate rhs of associated S-C equation
    double innerD1(double kx, double ky) const;
    double innerMu(double kx, double ky) const;
    double innerF0(double kx, double ky) const;
protected:
    const ZeroTempState& st;
};

#endif
