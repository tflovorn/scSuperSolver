/****************************************************************************
 * Copyright (C) 2010 Tim Lovorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include "State.hh"

State::State(const Environment& envIn) : env(envIn), 
    d1(envIn.initD1), mu(envIn.initMu), f0(envIn.initF0)
{
    setEpsilonMin();
}

// driver
bool State::makeSelfConsistent() {
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
bool State::checkSelfConsistent() const {
    return checkD1() && checkMu() && checkF0();
}

bool State::checkD1() const {
    return fabs(absErrorD1()) < env.tolD1;
}

bool State::checkMu() const {
    return fabs(absErrorMu()) < env.tolMu;
}

bool State::checkF0() const {
    return fabs(absErrorF0()) < env.tolF0;
}

// error calculators
double State::absErrorD1() const {
    double lhs = d1;
    double rhs = BZone::average((const State&)(*this), Spectrum::innerD1);
    return lhs - rhs;
}

double State::absErrorMu() const {
    double lhs = env.x;
    double rhs = BZone::average((const State&)(*this), Spectrum::innerMu);
    return lhs - rhs;
}

double State::absErrorF0() const {
    double lhs = 1.0 / (env.t0 + env.tz);
    double rhs = BZone::average((const State&)(*this), Spectrum::innerF0);
    return lhs - rhs;
}

double State::relErrorD1() const {
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

double State::relErrorMu() const {
    return fabs(absErrorMu()) / env.x;
}

double State::relErrorF0() const {
    return fabs(absErrorF0()) * (env.t0 + env.tz);
}

// getters
double State::getD1() const {
    return d1;
}

double State::getMu() const {
    return mu;
}

double State::getF0() const {
    return f0;
}

double State::getEpsilonMin() const {
    return epsilonMin;
}

// logging
void State::logState() const {
    std::string sc = checkSelfConsistent() ? "true" : "false";
    env.outputLog.printf("<begin>,state\n");
    env.outputLog.printf("self-consistent,%s\n", sc.c_str());
    env.outputLog.printf("d1,%e\nd1RelError,%e\n", getD1(), relErrorD1());
    env.outputLog.printf("mu,%e\nmuRelError,%e\n", getMu(), relErrorMu());
    env.outputLog.printf("f0,%e\nf0RelError,%e\n", getF0(), relErrorF0());
    env.outputLog.printf("<end>,state\n");
}

// variable manipulators
double State::setEpsilonMin() {
    epsilonMin = BZone::minimum((const State&)(*this), Spectrum::epsilonBar);
    return epsilonMin;
}

double State::helperD1(double x, void *params) {
    State *st = (State*)params;
    st->d1 = x;
    st->setEpsilonMin();    // D1 changed so epsilonMin might change
    return st->absErrorD1();
}

double State::helperMu(double x, void *params) {
    State *st = (State*)params;
    st->mu = x;
//    std::cout << "helperMu, about to echo mu\n";
    st->env.debugLog.printf("trying mu = %e, about to fix D1\n", x);
    st->fixD1();
    st->env.debugLog.printf("D1 fixed at %e\n", st->d1);
    return st->absErrorMu();
}

double State::helperF0(double x, void *params) {
    State *st = (State*)params;
    st->f0 = x;
//    std::cout << "helperF0, about to echo f0\n";
    st->env.debugLog.printf("trying f0 = %e, about to fix mu\n", x);
    st->fixMu();
    st->env.debugLog.printf("mu fixed at %e\n", st->mu);
    return st->absErrorF0();
}

bool State::fixD1() {
    double old_d1 = d1;
    RootFinder rootFinder(&State::helperD1, this, d1, 0.0, 1.0, env.tolD1 / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("D1 failed to converge!\n");
        d1 = old_d1;
        return false;
    }
    return true;
}

bool State::fixMu() {
    double old_mu = mu;
    RootFinder rootFinder(&State::helperMu, this, mu, -1.0, 1.0, 
                          env.tolMu / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("Mu failed to converge!\n");
        mu = old_mu;
        return false;
    }
    return true;
}

bool State::fixF0() {
    double old_f0 = f0;
    RootFinder rootFinder(&State::helperF0, this, f0, 0.0, 1.0, env.tolF0 / 10);
    const RootData& rootData = rootFinder.findRoot();
    if (!rootData.converged) {
        env.errorLog.printf("F0 failed to converge!\n");
        f0 = old_f0;
        return false;
    }
    return true;
}
