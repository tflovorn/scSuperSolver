#include "Controller.hh"

Controller::Controller(const ConfigData& config, const Environment& env, State& st) :
    myConfig(config), myEnv(env), myState(st) { }

Controller::~Controller() {
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}
