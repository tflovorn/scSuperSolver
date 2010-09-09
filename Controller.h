#ifndef __MFTS_CONTROLLER_H
#define __MFTS_CONTROLLER_H

#include <string>
#include <vector>

#include "Logger.h"
#include "ConfigData.h"
#include "Environment.h"
#include "State.h"

class Controller {
    // Factory for controller.
    static Controller& makeController(const std::string& fileName);
    // Delete config, env, state, and all loggers.
    ~Controller();
private:
    // List of all the loggers we'll use.
    std::vector<Logger> loggers;
    // The important bits.
    const ConfigData& myConfig; // Configuration file data.
    const Environment& myEnv;   // Data needed for State to do its work.
    State& myState;             // The thing that changes.
    // Build controller from given parts.
    Controller(const ConfigData& config, const Environment& env, State& st);
};

#endif
