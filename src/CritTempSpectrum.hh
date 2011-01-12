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
#include "BZone.hh"

struct OmegaCoeffs {
    double c_planar, c_perp, c_cross;
};

struct LambdaOutput {
    double plus, double minus;
};

struct InnerPiInput {
    InnerPiInput(const CritTempState& _st, double _omega, 
                 double _kx, double _ky);
    double omega, double kx, double ky;
    const CritTempState& st;
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
    // term to be summed to calculate rhs of associated S-C equation
    static double innerD1(const CritTempState& st, double kx, double ky);
    static double innerMu(const CritTempState& st, double kx, double ky);
    // term summed to calculate Re Pi (xx, xy, yy)
    static double innerPiCommon(const InnerPiInput& ipi, double qx, double qy);
    static double innerPiXX(const InnerPiInput& ipi, double qx, double qy);
    static double innerPiXY(const InnerPiInput& ipi, double qx, double qy);
    static double innerPiYY(const InnerPiInput& ipi, double qx, double qy);
    // BZone call required to calculate these.
    static double lambdaPlus(const CritTempState& st, double omega, 
                             double kx, double ky, double kz);
    static double lambdaMinus(const CritTempState& st, double omega, 
                              double kx, double ky, double kz);
    static LambdaOutput getLambda(const CritTempState& st, double omega, 
                                  double kx, double ky, double kz);
    static double getPiXX(const CritTempState& st, double omega, 
                          double kx, double ky);
    static double getPiXY(const CritTempState& st, double omega, 
                          double kx, double ky);
    static double getPiYY(const CritTempState& st, double omega,                                          double kx, double ky);
    // Requires solving for omega coefficients.  bc = (nu/x2)^(2/3)
    static double getNu(const CritTempState& st);
    // Requires finding the smallest root of lambda minus or plus.
    static OmegaCoeffs getOmegaCoeffs(const CritTempState& st);
    // Use this to check accuracy of OmegaCoeffs.
    static double omegaApprox(const OmegaCoeffs& oc, double kx, double ky, 
                              double kz);
    // Required to find root of lambda.
    double omegaExact(const CritTempState& st, double kx, double ky, double kz);
};

#endif
