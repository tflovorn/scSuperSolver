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

#include "PairTempSpectrum.hh"

double PairTempSpectrum::epsilon(const PairTempState& st, double kx, 
                                 double ky) {
    return epsilonBar(st, kx, ky) - st.getEpsilonMin();
}

double PairTempSpectrum::epsilonBar(const PairTempState& st, double kx, 
                                    double ky) {
    const PairTempEnvironment& env = st.env;
    const double sx = sin(kx);
    const double sy = sin(ky);
    return 2.0 * env.th * ((sx + sy) * (sx + sy) - 1.0)
         + 4.0 * (st.getD1() * env.t0 - env.thp) * sx * sy;
}

double PairTempSpectrum::xi(const PairTempState& st, double kx, double ky) {
    return epsilon(st, kx, ky) - st.getMu();
}

double PairTempSpectrum::fermi(const PairTempState& st, double energy) {
    return 1.0 / (exp(st.getBp() * energy) + 1.0);
}

double PairTempSpectrum::innerD1(const PairTempState& st, double kx, 
                                 double ky) {
    return -sin(kx) * sin(ky) * fermi(st, xi(st, kx, ky));
}

double PairTempSpectrum::innerMu(const PairTempState& st, double kx, 
                                 double ky) {
    return fermi(st, xi(st, kx, ky));
}

double PairTempSpectrum::innerBp(const PairTempState& st, double kx, 
                                 double ky) {
    const double sin_part = sin(kx) - sin(ky);
    return sin_part * sin_part * tanh(st.getBp() * xi(st, kx, ky) / 2.0) / 
           xi(st, kx, ky);
}
