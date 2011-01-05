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
    BaseState(envIn), env(envIn), bp(envIn.initBp) 
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
        fixBp();
        env.debugLog.printf("got bp = %e\n", bp);
    } while (!checkSelfConsistent());
    return checkSelfConsistent();
}

// checkers
bool CritTempState::checkSelfConsistent() const {
    return checkD1() && checkMu() && checkBp();
}

bool CritTempState::checkBp() const {
    return fabs(absErrorBp()) < env.tolBp;
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
// TODO
double CritTempState::absErrorBp() const {
    double lhs = 1.0 / (env.t0 + env.tz);
    double rhs = BZone::average<CritTempState>(*this, *this,
                                               CritTempSpectrum::innerBp);
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
// TODO
double CritTempState::relErrorBp() const {
    return fabs(absErrorBp()) * (env.t0 + env.tz);
}

// getters
double CritTempState::getBp() const {
    return bp;
}

// logging
void CritTempState::logState() const {
    std::string sc = checkSelfConsistent() ? "true" : "false";
    env.outputLog.printf("<begin>,state\n");
    env.outputLog.printf("self-consistent,%s\n", sc.c_str());
    env.outputLog.printf("d1,%e\nd1RelError,%e\n", getD1(), relErrorD1());
    env.outputLog.printf("mu,%e\nmuRelError,%e\n", getMu(), relErrorMu());
    env.outputLog.printf("bp,%e\nbpRelError,%e\n", getBp(), relErrorBp());
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

double CritTempState::helperBp(double x, void *params) {
    CritTempState *st = (CritTempState*)params;
    st->bp = x;
    st->env.debugLog.printf("trying bp = %e, about to fix mu\n", x);
    st->fixMu();
    st->env.debugLog.printf("mu fixed at %e\n", st->mu);
    return st->absErrorBp();
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

bool CritTempState::fixBp() {
    double old_bp = bp;
    RootFinder rootFinder(&CritTempState::helperBp, this, bp,
                          0.0, 1e6, env.tolBp / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("Bp failed to converge!\n");
        bp = old_bp;
        return false;
    }
    return true;
}
