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

#include "ZeroTempState.hh"

ZeroTempState::ZeroTempState(const ZeroTempEnvironment& envIn) : 
    BaseState(envIn), env(envIn), f0(envIn.initF0), spectrum(this)
{   
    setEpsilonMin();
}
// driver
bool ZeroTempState::makeSelfConsistent() {
    do {
        fixD1();
        env.debugLog.printf("got d1 = %e\n", d1);
        fixMu();
        env.debugLog.printf("got mu = %e\n", mu);
        fixF0();
        env.debugLog.printf("got f0 = %e\n", f0);
    } while (!checkSelfConsistent());
    return checkSelfConsistent();
}

// checkers
bool ZeroTempState::checkSelfConsistent() const {
    return checkD1() && checkMu() && checkF0();
}

bool ZeroTempState::checkF0() const {
    return fabs(absErrorF0()) < env.tolF0;
}

// error calculators
double ZeroTempState::absErrorD1() const {
    double lhs = d1;
    double rhs = BZone::average<ZeroTempState>(*this, *this, 
                                               ZeroTempSpectrum::innerD1);
    return lhs - rhs;
}

double ZeroTempState::absErrorMu() const {
    double lhs = env.x;
    double rhs = BZone::average<ZeroTempState>(*this, *this,
                                               ZeroTempSpectrum::innerMu);
    return lhs - rhs;
}

double ZeroTempState::absErrorF0() const {
    double lhs = 1.0 / (env.t0 + env.tz);
    double rhs = BZone::average<ZeroTempState>(*this, *this,
                                               ZeroTempSpectrum::innerF0);
    return lhs - rhs;
}

double ZeroTempState::relErrorD1() const {
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

double ZeroTempState::relErrorMu() const {
    return fabs(absErrorMu()) / env.x;
}

double ZeroTempState::relErrorF0() const {
    return fabs(absErrorF0()) * (env.t0 + env.tz);
}

// getters
double ZeroTempState::getF0() const {
    return f0;
}

// logging
void ZeroTempState::logState() const {
    std::string sc = checkSelfConsistent() ? "true" : "false";
    env.outputLog.printf("<begin>,state\n");
    env.outputLog.printf("self-consistent,%s\n", sc.c_str());
    env.outputLog.printf("d1,%e\nd1RelError,%e\n", getD1(), relErrorD1());
    env.outputLog.printf("mu,%e\nmuRelError,%e\n", getMu(), relErrorMu());
    env.outputLog.printf("f0,%e\nf0RelError,%e\n", getF0(), relErrorF0());
    env.outputLog.printf("<end>,state\n");
}

// variable manipulators
double ZeroTempState::setEpsilonMin() {
    epsilonMin = BZone::minimum<ZeroTempState>(*this, *this, 
                                               ZeroTempSpectrum::epsilonBar);
    return epsilonMin;
}

double ZeroTempState::helperD1(double x, void *params) {
    ZeroTempState *st = (ZeroTempState*)params;
    st->d1 = x;
    st->setEpsilonMin();    // D1 changed so epsilonMin might change
    return st->absErrorD1();
}

double ZeroTempState::helperMu(double x, void *params) {
    ZeroTempState *st = (ZeroTempState*)params;
    st->mu = x;
    st->env.debugLog.printf("trying mu = %e, about to fix D1\n", x);
    st->fixD1();
    st->env.debugLog.printf("D1 fixed at %e\n", st->d1);
    return st->absErrorMu();
}

double ZeroTempState::helperF0(double x, void *params) {
    ZeroTempState *st = (ZeroTempState*)params;
    st->f0 = x;
    st->env.debugLog.printf("trying f0 = %e, about to fix mu\n", x);
    st->fixMu();
    st->env.debugLog.printf("mu fixed at %e\n", st->mu);
    return st->absErrorF0();
}

bool ZeroTempState::fixD1() {
    double old_d1 = d1;
    RootFinder rootFinder(&ZeroTempState::helperD1, this, d1, 
                          0.0, 1.0, env.tolD1 / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("D1 failed to converge!\n");
        d1 = old_d1;
        return false;
    }
    return true;
}

bool ZeroTempState::fixMu() {
    double old_mu = mu;
    RootFinder rootFinder(&ZeroTempState::helperMu, this, mu, 
                          -1.0, 1.0, env.tolMu / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("Mu failed to converge!\n");
        mu = old_mu;
        return false;
    }
    return true;
}

bool ZeroTempState::fixF0() {
    double old_f0 = f0;
    RootFinder rootFinder(&ZeroTempState::helperF0, this, f0, 
                          0.0, 1.0, env.tolF0 / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("F0 failed to converge!\n");
        f0 = old_f0;
        return false;
    }
    return true;
}
