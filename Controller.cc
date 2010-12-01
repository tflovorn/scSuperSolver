/****************************************************************************
 * Copyright (C) 2010 Tim Lovorn
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

#include "Controller.hh"

Controller::Controller(const ConfigData& config, const Environment& env, 
    State& st) : myConfig(config), myEnv(env), myState(st) { }

Controller::~Controller() {
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}

Controller& Controller::makeController(const std::string& cfgFileName) {
    ConfigData *cfg = new ConfigData(cfgFileName);
    Environment *env = new Environment((const ConfigData&)(*cfg));
    State *st = new State((const Environment&)(*env));
    Controller *control = new Controller((const ConfigData&)cfg, 
        (const Environment&)(*env), (State&)(*st));
    return (Controller&)(*control);
}

bool Controller::selfConsistentCalc() {
    return myState.makeSelfConsistent();
}

void Controller::logState() {
    myState.logState();
}

void Controller::logConfig() {

}
