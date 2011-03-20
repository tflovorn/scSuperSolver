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

LambdaInput::LambdaInput(const CritTempState& _st, double _kx, double _ky,
                         double _kz, double _lambdaMinus) :
    st(_st), kx(_kx), ky(_ky), kz(_kz), lambdaMinus(_lambdaMinus) { }

InnerPiInput::InnerPiInput(const CritTempState& _st, double _omega, 
                           double _kx, double _ky) :
    st(_st), omega(_omega), kx(_kx), ky(_ky) { }

PiOutput::PiOutput(double _xx, double _xy, double _yy) :
    xx(_xx), xy(_xy), yy(_yy) { }

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
    return 1.0 / (exp(st.getBc() * energy) + 1.0);
}

double CritTempSpectrum::bose(const CritTempState& st, double energy) {
    return 1.0 / (exp(st.getBc() * energy) - 1.0);
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
    return sin_part * sin_part * tanh(st.getBc() * xi(st, kx, ky) / 2.0) / 
           xi(st, kx, ky);
}

double CritTempSpectrum::innerPiCommon(const InnerPiInput& ipi, 
                                       double qx, double qy) {
    const CritTempState st = ipi.st;
    double xiPlus = xi(st, qx + ipi.kx / 2, qy + ipi.ky / 2);
    double xiMinus = xi(st, qx - ipi.kx / 2, qy - ipi.ky / 2);
    double common = -(tanh(st.getBc() * xiPlus / 2) + tanh(st.getBc() 
        * xiMinus / 2)) / (ipi.omega - xiPlus - xiMinus);
    return common;
}

double CritTempSpectrum::innerPiXX(const InnerPiInput& ipi, 
                                   double qx, double qy) {
    double common = innerPiCommon(ipi, qx, qy);
    return sin(qx) * sin(qx) * common;
}

double CritTempSpectrum::innerPiXY(const InnerPiInput& ipi, 
                                   double qx, double qy) {
    double common = innerPiCommon(ipi, qx, qy);
    return sin(qx) * sin(qy) * common;
}

double CritTempSpectrum::innerPiYY(const InnerPiInput& ipi, 
                                   double qx, double qy) {
    double common = innerPiCommon(ipi, qx, qy);
    return sin(qy) * sin(qy) * common;
}

double CritTempSpectrum::getLambda(double omega, void *params) {
    LambdaInput *lin = (LambdaInput*)params;
    const CritTempState& st = lin->st;
    double kx = lin->kx, ky = lin->ky, kz = lin->kz;

    double ex = 2 * (st.env.t0 * cos(ky) + st.env.tz * cos(kz)),
           ey = 2 * (st.env.t0 * cos(kx) + st.env.tz * cos(kz));
    PiOutput Pi = getPi(st, omega, kx, ky);
    double firstTerm = (ex * Pi.xx + ey * Pi.yy) / 2 - 1;
    double secondTerm = sqrt(pow((ex * Pi.xx - ey * Pi.yy), 2.0) / 4
        + ex * ey * pow(Pi.xy, 2.0));

    if (lin->lambdaMinus) {
        return firstTerm - secondTerm;
    } else {
        return firstTerm + secondTerm;
    } 
}

PiOutput CritTempSpectrum::getPi(const CritTempState& st, double omega,
                                 double kx, double ky) {
    InnerPiInput ipi(st, omega, kx, ky);
    double piXX = BZone::average<InnerPiInput>(st, ipi, innerPiXX);
    double piXY = BZone::average<InnerPiInput>(st, ipi, innerPiXY);
    double piYY = BZone::average<InnerPiInput>(st, ipi, innerPiYY);
    PiOutput out(piXX, piXY, piYY);
    return out;
}

double CritTempSpectrum::nuFunction(double y, void *params) {
    return sqrt(y) / (exp(y) - 1);
}

double CritTempSpectrum::getNu(const CritTempState& st) {
    OmegaCoeffs ocs = getOmegaCoeffs(st);
    Integrator integrator(&nuFunction, NULL, 1e-6, 1e-6);
    double integral = integrator.doIntegral(0.0, -2 * st.getMu() * st.getBc(),
                                            st.env.errorLog);
    st.env.debugLog.printf("integral = %e\n"
                           "planar = %e cross = %e perp = %e\n", integral,
                           ocs.planar, ocs.cross, ocs.perp);
    double coeffPart = sqrt((ocs.planar + ocs.cross / 2.0) * 
                            (ocs.planar - ocs.cross / 2.0) * ocs.perp);
    return integral / (4 * pow(M_PI, 2.0) * coeffPart);
}

OmegaCoeffs CritTempSpectrum::getOmegaCoeffs(const CritTempState& st) {
    double small_k = 0.05, sks = small_k * small_k;
    OmegaCoeffs ocs;
    ocs.planar = omegaExact(st, small_k, 0.0, 0.0) / sks;
    ocs.perp = omegaExact(st, 0.0, 0.0, small_k) / sks;
    ocs.cross = omegaExact(st, small_k, small_k, 0.0) / sks - 2 * ocs.planar;
    return ocs;
}

double CritTempSpectrum::omegaApprox(const OmegaCoeffs& oc,
                                     double kx, double ky, double kz) {
    return oc.planar * (kx * kx + ky * ky) + oc.perp * kz * kz
         + oc.cross * kx * ky;
}

double CritTempSpectrum::omegaExact(const CritTempState& st, 
                                    double kx, double ky, double kz) {
    LambdaInput lin(st, kx, ky, kz, true);
    RootFinder rf(&CritTempSpectrum::getLambda, &lin, 1.0, 0.0, 100.0, 
                  1e-6);
    const RootData& rootData = rf.findRoot();
    if (!rootData.converged) {
        st.env.errorLog.printf("Failed to find root of Lambda at"
                               " k = (%f, %f, %f)\n", kx, ky, kz);
        return -1;
    }
    return rootData.root;
}
