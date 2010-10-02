#include "State.hh"

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

// error calculators STUBS
double State::errorD1() const {
    return 0.0;
}

double State::errorMu() const {
    return 0.0;
}

double State::errorF0() const {
    return 0.0;
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

// variable manipulators STUBS
double State::setEpsilonMin() {
    return 0.0;
}

double State::fixD1() {
    return 0.0;
}

double State::fixMu() {
    return 0.0;
}

double State::fixF0() {
    return 0.0;
}
