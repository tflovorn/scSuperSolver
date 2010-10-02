#include <iostream>
#include <cmath>

#include "Environment.hh"
#include "ConfigData.hh"
#include "State.hh"
#include "BZone.hh"

double test_1(const State& st, double kx, double ky) {
    return 1.0;
}

double test_sin(const State& st, double kx, double ky) {
    return sin(kx) + sin(ky);
}

int main(int argc, char *argv[]) {
    const std::string& cfgFileName = "test_cfg";
    const ConfigData& cfg = ConfigData::makeFromFile(cfgFileName);
    const Environment& env(cfg);
    State st(env);
    std::cout << BZone::average(st, test_1) << std::endl;
    std::cout << BZone::average(st, test_sin) << std::endl;
}
