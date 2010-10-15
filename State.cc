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
    } while (!checkSelfConsistent());
    return checkSelfConsistent();
}

// checkers
bool State::checkSelfConsistent() const {
    return checkD1() && checkMu() && checkF0();
}

bool State::checkD1() const {
    return absErrorD1() < env.tolD1;
}

bool State::checkMu() const {
    return absErrorMu() < env.tolMu;
}

bool State::checkF0() const {
    return absErrorF0() < env.tolF0;
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

double State::fixD1() {
    RootFinder rf(&State::helperD1, this, d1, 0.0, 10.0, 1e-6);
    const RootData& rd = rf.findRoot();
    return d1;
}

double State::fixMu() {
    RootFinder rf(&State::helperMu, this, mu, -10.0, 10.0, 1e-6);
    const RootData& rd = rf.findRoot();
    return mu;
}

double State::fixF0() {
    RootFinder rf(&State::helperF0, this, f0, 0.0, 10.0, 1e-6);
    const RootData& rd = rf.findRoot();
    return f0;
}
