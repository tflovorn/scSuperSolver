#include "Controller.hh"

Controller::Controller(const ConfigData& config, const Environment& env, State& st) :
    myConfig(config), myEnv(env), myState(st) { }

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

void Controller::logResults() {
/*
    std::string sc = myState.checkSelfConsistent ? "true" : "false";
    env.outputLog.writeln(std::string("self-consistent: ") << sc);
    env.outputLog.writeln(std::string("D1: ") << myState.getD1() << 
                          " error: " << myState.absErrorD1());
    env.outputLog.writeln(std::string("mu: ") << myState.getMu() << 
                          " error: " << myState.absErrorMu());
    env.outputLog.writeln(std::string("F0: ") << myState.getF0() << 
                          " error: " << myState.absErrorF0());
*/
}

void Controller::logConfig() {

}
