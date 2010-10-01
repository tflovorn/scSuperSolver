#include "Controller.h"

/*
Controller::Controller(const ConfigData& config, const Environment& env, State& st) :
    myConfig(config), myEnv(env), myState(st)
{
    
}
*/

Controller::~Controller() {
    delete &errorLog;
    delete &outputLog;
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}
