#include "Controller.hh"

Controller::Controller(const ConfigData& config, const Environment& env, 
    State& st) : myConfig(config), myEnv(env), myState(st) { }

Controller::~Controller() {
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}

Controller& Controller::makeController(const std::string& cfgFileName) {
    const ConfigData& cfg = ConfigData::makeFromFile(cfgFileName);
    Environment *env = new Environment(cfg);
    State *st = new State((const Environment&)(*env));
    Controller *control = new Controller(cfg, (const Environment&)(*env),
                                               (State&)(*st));
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
