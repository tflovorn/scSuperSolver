#ifndef __MFTS_CONTROLLER_H
#define __MFTS_CONTROLLER_H

#include <string>

#include "Logger.hh"
#include "ConfigData.hh"
#include "Environment.hh"
#include "State.hh"

class Controller {
    // Factory for controller.  Make ConfigData from inFileName, Environment
    // from ConfigData, and State from Environment.  Then make a Controller.
    static Controller& makeController(const std::string& cfgFileName);
    // Delete config, env (which deletes loggers), and state.
    ~Controller();
    // Do the self-consistent calculation.  Return false if can't converge.
    bool selfConsistentCalc();
    // Output important data about current State.
    void logResults();
    // Output configuration data.
    void logConfig();
private:
    // The important bits of data.
    const ConfigData& myConfig;
    const Environment& myEnv; 
    State& myState;
    // Build controller from given important bits.
    Controller(const ConfigData& config, const Environment& env, State& st);
};

#endif
