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

#include "Controller.hh"

Controller::Controller(const ConfigData& config, 
                       const BaseEnvironment& env, BaseState& st) : 
    myConfig(config), myEnv(env), myState(st) 
{ }

Controller::~Controller() {
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}

Controller& Controller::makeController(const std::string& path,
                                       const std::string& cfgFileName) {
    Controller *control;
    ConfigData *cfg = new ConfigData(path, cfgFileName);
    std::string type = cfg->getValue<std::string>("calculationType");
    if (type == "pairTemp") {
        PairTempEnvironment *env = new PairTempEnvironment(*cfg);
        PairTempState *st = new PairTempState(*env);
        control = new Controller(*cfg, *env, *st);
    } else if (type == "zeroTemp") {
        ZeroTempEnvironment *env = new ZeroTempEnvironment(*cfg);
        ZeroTempState *st = new ZeroTempState(*env);
        control = new Controller(*cfg, *env, *st);
    }
    return (Controller&)(*control);
}

bool Controller::selfConsistentCalc() {
    return myState.makeSelfConsistent();
}

void Controller::logState() {
    myState.logState();
}

void Controller::logConfig() {
    myConfig.writeToLog(myEnv.outputLog);
}
