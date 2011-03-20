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

#include "CritTempState.hh"

CritTempState::CritTempState(const CritTempEnvironment& envIn) : 
    BaseState(envIn), env(envIn), bc(envIn.initBc) 
{   
    setEpsilonMin();
}

// driver
bool CritTempState::makeSelfConsistent() {
    do {
        fixD1();
        env.debugLog.printf("got d1 = %e\n", d1);
        fixMu();
        env.debugLog.printf("got mu = %e\n", mu);
        fixBc();
        env.debugLog.printf("got bc = %e\n", bc);
    } while (!checkSelfConsistent());
    return checkSelfConsistent();
}

// checkers
bool CritTempState::checkSelfConsistent() const {
    return checkD1() && checkMu() && checkBc();
}

bool CritTempState::checkBc() const {
    return fabs(absErrorBc()) < env.tolBc;
}

// error calculators
double CritTempState::absErrorD1() const {
    double lhs = d1;
    double rhs = BZone::average<CritTempState>(*this, *this, 
                                               CritTempSpectrum::innerD1);
    return lhs - rhs;
}

double CritTempState::absErrorMu() const {
    double lhs = 1.0 / (env.t0 + env.tz);
    double rhs = BZone::average<CritTempState>(*this, *this,
                                               CritTempSpectrum::innerMu);
    return lhs - rhs;
}

double CritTempState::absErrorBc() const {
    double nu = CritTempSpectrum::getNu(*this);
    double rhs = pow(nu / getX2(), 2.0 / 3.0);

    double lhs = bc;
    return lhs - rhs;
}

double CritTempState::relErrorD1() const {
    double error = absErrorD1();
    if (d1 == 0.0 && error == 0.0) {
        return 0.0;
    }
    else if (d1 == 0.0) {
        return fabs(d1) / fabs(absErrorD1());
    }
    else {
        return fabs(absErrorD1()) / fabs(d1);
    }
}

double CritTempState::relErrorMu() const {
    return fabs(absErrorMu()) * (env.t0 + env.tz);
}

double CritTempState::relErrorBc() const {
    return fabs(absErrorBc()) / bc;
}

// getters
double CritTempState::getBc() const {
    return bc;
}

double CritTempState::getX1() const {
    return BZone::average<CritTempState>(*this, *this,
                                         CritTempSpectrum::innerX1);
}

double CritTempState::getX2() const {
    return env.x - getX1();
}

// logging
void CritTempState::logState() const {
    std::string sc = checkSelfConsistent() ? "true" : "false";
    env.outputLog.printf("<begin>,state\n");
    env.outputLog.printf("self-consistent,%s\n", sc.c_str());
    env.outputLog.printf("d1,%e\nd1RelError,%e\n", getD1(), relErrorD1());
    env.outputLog.printf("mu,%e\nmuRelError,%e\n", getMu(), relErrorMu());
    env.outputLog.printf("bc,%e\nbcRelError,%e\n", getBc(), relErrorBc());
    env.outputLog.printf("<end>,state\n");
}

// variable manipulators
double CritTempState::setEpsilonMin() {
    epsilonMin = BZone::minimum<CritTempState>(*this, *this, 
                                               CritTempSpectrum::epsilonBar);
    return epsilonMin;
}

double CritTempState::helperD1(double x, void *params) {
    CritTempState *st = (CritTempState*)params;
    st->d1 = x;
    st->setEpsilonMin();    // D1 changed so epsilonMin might change
    return st->absErrorD1();
}

double CritTempState::helperMu(double x, void *params) {
    CritTempState *st = (CritTempState*)params;
    st->mu = x;
    st->env.debugLog.printf("trying mu = %e, about to fix D1\n", x);
    st->fixD1();
    st->env.debugLog.printf("D1 fixed at %e\n", st->d1);
    return st->absErrorMu();
}

bool CritTempState::fixD1() {
    double old_d1 = d1;
    RootFinder rootFinder(&CritTempState::helperD1, this, d1, 
                          0.0, 1.0, env.tolD1 / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("D1 failed to converge!\n");
        d1 = old_d1;
        return false;
    }
    return true;
}

bool CritTempState::fixMu() {
    double old_mu = mu;
    RootFinder rootFinder(&CritTempState::helperMu, this, mu, 
                          -1.0, 0.0, env.tolMu / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("Mu failed to converge!\n");
        mu = old_mu;
        return false;
    }
    return true;
}

bool CritTempState::fixBc() {
    double old_bc = bc, last_bc = bc;
    for (int iterCount = 0; iterCount < BC_MAX_ITERS; iterCount++) {
        double nu = CritTempSpectrum::getNu(*this);
        env.debugLog.printf("nu = %e, x2 = %e\n", nu, getX2());
        bc = pow(nu / getX2(), 2.0 / 3.0);
        env.debugLog.printf("setting bc to %e\n", bc);
        if (fabs(bc - last_bc) / bc < env.tolBc) {
            return true;
        }
    }
    env.errorLog.printf("Bc failed to converge!\n");
    bc = old_bc;
    return false;
}
