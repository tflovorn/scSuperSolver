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

#ifndef __SCSS_CONTROLLER_H
#define __SCSS_CONTROLLER_H

#include <string>

#include "ConfigData.hh"
#include "BaseState.hh"
#include "BaseEnvironment.hh"
#include "ZeroTempEnvironment.hh"
#include "ZeroTempState.hh"
#include "PairTempEnvironment.hh"
#include "PairTempState.hh"
#include "CritTempEnvironment.hh"
#include "CritTempState.hh"

class Controller {
public:
    // Factory for controller.  Make ConfigData from inFileName, Environment
    // from ConfigData, and State from Environment.  Then make a Controller.
    static Controller& makeController(const std::string& path,
                                      const std::string& cfgFileName);
    // Build controller from given important bits.
    Controller(const ConfigData& config, const BaseEnvironment& env, 
               BaseState& st);
    // Delete config, env (which deletes loggers), and state.
    ~Controller();
    // Do the self-consistent calculation.  Return false if can't converge.
    bool selfConsistentCalc();
    // Output important data about current State.
    void logState();
    // Output configuration data.
    void logConfig();
private:
    // The important bits of data.
    const ConfigData& myConfig;
    const BaseEnvironment& myEnv; 
    BaseState& myState;
};

#endif
