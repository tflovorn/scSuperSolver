#include "Controller.hh"

Controller::Controller(const ConfigData& config, const Environment& env, State& st) :
    myConfig(config), myEnv(env), myState(st) { }

Controller::~Controller() {
    delete &myState;
    delete &myEnv;
    delete &myConfig;
}

bool Controller::selfConsistentCalc() {
    return myState.makeSelfConsistent();
}

void Controller::logResults() {
    string sc = st.checkSelfConsistent ? "true" : "false";
    env.outputLog.writeln("self-consistent: " << sc);
    env.outputLog.writeln("D1: " << st.getD1() << 
                          " error: " << st.absErrorD1());
    env.outputLog.writeln("mu: " << st.getMu() << 
                          " error: " << st.absErrorMu());
    env.outputLog.writeln("F0: " << st.getF0() << 
                          " error: " << st.absErrorF0());
}

void Controller::logConfig() {

}
