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
    std::string sc = myState.checkSelfConsistent() ? "true" : "false";
    myEnv.outputLog.printf("self-consistent: %s\n", sc.c_str());
    myEnv.outputLog.printf("D1: %e; error: %e\n", myState.getD1(), 
                                                  myState.absErrorD1());
    myEnv.outputLog.printf("mu: %e; error: %e\n", myState.getMu(),
                                                  myState.absErrorMu());
    myEnv.outputLog.printf("F0: %e; error: %e\n", myState.getF0(),
                                                  myState.absErrorF0());
}

void Controller::logConfig() {

}
