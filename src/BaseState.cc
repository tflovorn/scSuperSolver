/*
  Copyright (c) 2010 Timothy Lovorn

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

#include "BaseState.hh"

BaseState::BaseState(const BaseEnvironment& envIn) : 
    env(envIn), d1(envIn.initD1), mu(envIn.initMu), spectrum(this)
{ }

// checkers
bool BaseState::checkD1() const {
    return fabs(absErrorD1()) < env.tolD1;
}

bool BaseState::checkMu() const {
    return fabs(absErrorMu()) < env.tolMu;
}

// getters
double BaseState::getD1() const {
    return d1;
}

double BaseState::getMu() const {
    return mu;
}

double BaseState::getEpsilonMin() const {
    return epsilonMin;
}

// variable manipulators
double BaseState::setEpsilonMin() {
    epsilonMin = BZone::minimum<BaseState>(*this, *this, spectrum.epsilonBar);
    return epsilonMin;
}

