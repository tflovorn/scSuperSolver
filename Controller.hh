/****************************************************************************
 * Copyright (C) 2010 Timothy Lovorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef __MFTS_CONTROLLER_H
#define __MFTS_CONTROLLER_H

#include <string>

#include "Logger.hh"
#include "ConfigData.hh"
#include "Environment.hh"
#include "State.hh"

class Controller {
public:
    // Factory for controller.  Make ConfigData from inFileName, Environment
    // from ConfigData, and State from Environment.  Then make a Controller.
    static Controller& makeController(const std::string& cfgFileName);
    // Build controller from given important bits.
    Controller(const ConfigData& config, const Environment& env, State& st);
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
    const Environment& myEnv; 
    State& myState;
};

#endif
