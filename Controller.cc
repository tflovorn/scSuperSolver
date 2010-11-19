#include "Controller.hh"

Controller::Controller(const ConfigData& config, const Environment& env, 
    State& st) : myConfig(config), myEnv(env), myState(st) { }

Controller::~Controller() {
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}

Controller& Controller::makeController(const std::string& cfgFileName) {
    ConfigData *cfg = new ConfigData();
    cfg->readFromFile(cfgFileName);
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
