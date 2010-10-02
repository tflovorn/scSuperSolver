#include <iostream>

#include "Logger.hh"
#include "ConfigData.hh"
#include "Environment.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName = "test_ConfigData_cfg";
    const ConfigData& cfg = ConfigData::makeFromFile(cfgFileName);
    const Environment& env(cfg);
    env.outputLog.write("Output log is running!");
    env.errorLog.write("Error log is running!  Hooray!");
    std::cout << env.x << std::endl;
}
