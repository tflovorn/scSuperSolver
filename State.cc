#include <cmath>
#include <iostream>

#include "State.hh"
#include "Spectrum.hh"
#include "BZone.hh"
#include "RootFinder.hh"

State::State(const Environment& envIn) : env(envIn), 
    d1(envIn.initD1), mu(envIn.initMu), f0(envIn.initF0)
{
    setEpsilonMin();
}

// driver
bool State::makeSelfConsistent() {
    do {
        fixD1();
        fixMu();
        fixF0();
        logState();
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
    return fabs(absErrorD1()) / fabs(d1);
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
    env.outputLog.printf("self-consistent: %s\n", sc.c_str());
    env.outputLog.printf("D1: %e; error: %e\n", getD1(), absErrorD1());
    env.outputLog.printf("mu: %e; error: %e\n", getMu(), absErrorMu());
    env.outputLog.printf("F0: %e; error: %e\n", getF0(), absErrorF0());
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
    return st->absErrorMu();
}

double State::helperF0(double x, void *params) {
    State *st = (State*)params;
    st->f0 = x;
    return st->absErrorF0();
}

bool State::fixD1() {
    double old_d1 = d1;
    RootFinder rf(&State::helperD1, this, d1, 0.0, 10.0, env.tolD1 / 100);
    const RootData& rd = rf.findRoot();
    if (!rd.converged) {
        env.errorLog.printf("D1 failed to converge!\n");
        d1 = old_d1;
        return false;
    }
    return true;
}

bool State::fixMu() {
    double old_mu = mu;
    RootFinder rf(&State::helperMu, this, mu, -10.0, 10.0, env.tolMu / 100);
    const RootData& rd = rf.findRoot();
    if (!rd.converged) {
        env.errorLog.printf("Mu failed to converge!\n");
        mu = old_mu;
        return false;
    }
    return true;
}

bool State::fixF0() {
    double old_f0 = f0;
    RootFinder rf(&State::helperF0, this, f0, 0.0, 10.0, env.tolF0 / 100);
    const RootData& rd = rf.findRoot();
    if (!rd.converged) {
        env.errorLog.printf("F0 failed to converge!\n");
        f0 = old_f0;
        return false;
    }
    return true;
    return f0;
}
