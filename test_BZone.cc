#include <iostream>
#include <cmath>
#include <cassert>

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

double test_step(const State& st, double kx, double ky) {
    if (kx > 0 && ky > 0) {
        return -1;
    }
    else {
        return 1;
    } 
}

int main(int argc, char *argv[]) {
    std::cout << "Starting BZone test." << std::endl;
    const std::string& cfgFileName = "test_cfg";
    ConfigData *cfg = new ConfigData();
    cfg->readFromFile(cfgFileName);
    const Environment& env((const ConfigData&)cfg);
    State st(env);

    double avg_1 = BZone::average(st, test_1);
    assert(avg_1 == 1);
    std::cout << "avg_1 = " << avg_1 << std::endl;

    double sin_tol = 1e-17;
    double avg_sin = BZone::average(st, test_sin);
    assert(avg_sin < sin_tol);
    std::cout << "avg_sin = " << avg_sin << std::endl;

    double min_step = BZone::minimum(st, test_step);
    assert(min_step == -1);
    std::cout << "min_step = " << min_step << std::endl;

    std::cout << "BZone passed all tests!" << std::endl;
    return 0;
}
