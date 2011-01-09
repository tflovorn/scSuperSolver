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

#include "CritTempSpectrum.hh"

InnerPiInput::InnerPiInput(const CritTempState& _st, double _omega, 
                           double _kx, double _ky) :
    st(_st), omega(_omega), kx(_kx), ky(_ky) { }

double CritTempSpectrum::epsilon(const CritTempState& st, double kx, 
                                 double ky) {
    return epsilonBar(st, kx, ky) - st.getEpsilonMin();
}

double CritTempSpectrum::epsilonBar(const CritTempState& st, double kx, 
                                    double ky) {
    const CritTempEnvironment& env = st.env;
    const double sx = sin(kx);
    const double sy = sin(ky);
    return 2.0 * env.th * ((sx + sy) * (sx + sy) - 1.0)
         + 4.0 * (st.getD1() * env.t0 - env.thp) * sx * sy;
}

double CritTempSpectrum::xi(const CritTempState& st, double kx, double ky) {
    return epsilon(st, kx, ky) - st.getMu();
}

double CritTempSpectrum::fermi(const CritTempState& st, double energy) {
    return 1.0 / (exp(st.getBp() * energy) + 1.0);
}

double CritTempSpectrum::bose(const CritTempState& st, double energy) {
    return 1.0 / (exp(st.getBp() * energy) - 1.0);
}

double CritTempSpectrum::innerX1(const CritTempState& st, double kx, 
                                 double ky) {
    return fermi(st, xi(st, kx, ky));
}

double CritTempSpectrum::innerD1(const CritTempState& st, double kx, 
                                 double ky) {
    return -sin(kx) * sin(ky) * fermi(st, xi(st, kx, ky));
}

double CritTempSpectrum::innerMu(const CritTempState& st, double kx, 
                                 double ky) {
    const double sin_part = sin(kx) - sin(ky);
    return sin_part * sin_part * tanh(st.getBp() * xi(st, kx, ky) / 2.0) / 
           xi(st, kx, ky);
}

PiOutput CritTermSpectrum::innerPi(const InnerPiInput& ipi, 
                                   double qx, double qy) {
    PiOutput out;
    const CritTempState st = ipi.st;
    double xiPlus = xi(st, qx + ipi.kx / 2, qy + ipi.ky / 2)
    double xiMinus = xi(st, qx - ipi.kx / 2, qy - ipi.ky / 2)
    double common = -(tanh(st.getBc() * xiPlus / 2) + tanh(st.getBc() 
        * xiMinus / 2)) / (ipi.omega - xiPlus - xMinus);
    out.xx = sin(qx) * sin(qx) * common;
    out.xy = sin(qx) * sin(qy) * common;
    out.xx = sin(qy) * sin(qy) * common;
    return out;
}

LambdaOutput CritTempSpectrum::getLambda(const CritTempState& st, 
        double omega, double kx, double ky, double kz) const {
    double ex = 2 * (st.env.t0 * cos(ky) + st.env.tz * cos(kz)),
           ey = 2 * (st.env.t0 * cos(kx) + st.env.tz * cos(kz));
    PiOutput Pi = getPi(st, omega, kx, ky);
    double firstTerm = (ex * Pi.xx + ey * Pi.yy) / 2 - 1;
    double secondTerm = sqrt(pow((ex * Pi.xx - ey * Pi.yy), 2.0) / 4
        + ex * ey * pow(Pi.xy, 2.0));
    LambdaOutput out;
    out.plus = firstTerm + secondTerm;
    out.minus = firstTerm - secondTerm;
    return out;
}

PiOutput CritTempSpectrum::getPi(const CritTempState& st, double omega,
                                 double kx, double ky) const {
    InnerPiInput ipi(st, omega, kx, ky);
    double BZone::average<InnerPiInput>(st, ipi, innerPi);
    
}

double CritTempSpectrum::getNu(const CritTempState& st) const {

}

OmegaCoeffs CritTempSpectrum::getOmegaCoeffs(const CritTempState& st) const {

}

double CritTempSpectrum::omegaApprox(const OmegaCoeffs& oc,
                                     double kx, double ky, double kz) {
    return oc.c_planar * (kx * kx + ky * ky) + oc.c_perp * kz * kz
         + oc.c_cross * kx * ky;
}

double CritTempSpectrum::omegaExact(const CritTempState& st, 
                                    double kx, double ky, double kz) {

}