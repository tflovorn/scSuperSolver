#include <cmath>

#include "State.hh"
#include "Spectrum.hh"
#include "BZone.hh"

State::State(const Environment& envIn) : env(envIn), 
    d1(envIn.initD1), mu(envIn.initMu), f0(envIn.initF0)
{
    setEpsilonMin();
}

// driver STUB
bool State::makeSelfConsistent() {
    return false;
}

// checkers
bool State::checkSelfConsistent() const {
    return checkD1() && checkMu() && checkF0();
}

bool State::checkD1() const {
    return errorD1() < env.tolD1;
}

bool State::checkMu() const {
    return errorMu() < env.tolMu;
}

bool State::checkF0() const {
    return errorF0() < env.tolF0;
}

// error calculators
double State::errorD1() const {
    double lhs = d1;
    double rhs = BZone::average((const State&)(*this), Spectrum::innerD1);
    return fabs(lhs - rhs) / lhs;
}

double State::errorMu() const {
    double lhs = env.x;
    double rhs = BZone::average((const State&)(*this), Spectrum::innerMu);
    return fabs(lhs - rhs) / lhs;
}

double State::errorF0() const {
    double lhs = 1.0 / (env.t0 + env.tz);
    double rhs = BZone::average((const State&)(*this), Spectrum::innerF0);
    return fabs(lhs - rhs) / lhs;
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
// STUBS
double State::fixD1() {
    return 0.0;
}

double State::fixMu() {
    return 0.0;
}

double State::fixF0() {
    return 0.0;
}
