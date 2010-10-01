#include "State.hh"

State::State(const Environment& envIn) : env(envIn) {
    d1 = env.initD1;
    mu = env.initMu;
    f0 = env.initF0;
    setEpsilonMin();
}

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
