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

#include "ZeroTempSpectrum.hh"

double ZeroTempSpectrum::epsilon(const ZeroTempState& st, double kx, 
                                 double ky) {
    return epsilonBar(st, kx, ky) - st.getEpsilonMin();
}

double ZeroTempSpectrum::epsilonBar(const ZeroTempState& st, double kx, 
                                    double ky) {
    const ZeroTempEnvironment& env = st.env;
    const double sx = sin(kx);
    const double sy = sin(ky);
    return 2.0 * env.th * ((sx + sy) * (sx + sy) - 1.0)
         + 4.0 * (st.getD1() * env.t0 - env.thp) * sx * sy;
}

double ZeroTempSpectrum::xi(const ZeroTempState& st, double kx, double ky) {
    return epsilon(st, kx, ky) - st.getMu();
}

double ZeroTempSpectrum::delta(const ZeroTempState& st, double kx, double ky) {
    return 4.0 * st.getF0() * (st.env.t0 + st.env.tz)
               * (sin(kx) + st.env.alpha * sin(ky));
}

double ZeroTempSpectrum::pairEnergy(const ZeroTempState& st, double kx, 
                                    double ky) {
    const double xi_k = xi(st, kx, ky);
    const double delta_k = delta(st, kx, ky);
    return sqrt(xi_k * xi_k + delta_k * delta_k);
}

double ZeroTempSpectrum::fermi(const ZeroTempState& st, double energy) {
    if (energy <= 0.0) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

double ZeroTempSpectrum::innerD1(const ZeroTempState& st, double kx, 
                                 double ky) {
    return -0.5*(1 - xi(st, kx, ky)/pairEnergy(st, kx, ky)) * sin(kx)*sin(ky);
}

double ZeroTempSpectrum::innerMu(const ZeroTempState& st, double kx, 
                                 double ky) {
    return 0.5 * (1 - xi(st, kx, ky)/pairEnergy(st, kx, ky));
}

double ZeroTempSpectrum::innerF0(const ZeroTempState& st, double kx, 
                                 double ky) {
    const double sin_part = sin(kx) + st.env.alpha * sin(ky);
    return sin_part * sin_part / pairEnergy(st, kx, ky);
}
