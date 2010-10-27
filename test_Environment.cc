#include <iostream>

#include "Logger.hh"
#include "ConfigData.hh"
#include "Environment.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName = "test_cfg";
    const ConfigData& cfg = ConfigData::makeFromFile(cfgFileName);
    const Environment& env(cfg);
    env.outputLog.printf("Output log is running!\n");
    env.errorLog.printf("Error log is running!  Hooray!\n");
    std::cout << env.x << std::endl;
}
