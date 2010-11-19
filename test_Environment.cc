#include <iostream>

#include "Logger.hh"
#include "ConfigData.hh"
#include "Environment.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName = "test_cfg";
    ConfigData *cfg = new ConfigData();
    cfg->readFromFile(cfgFileName);
    const Environment& env((const ConfigData&)(*cfg));
    env.outputLog.printf("Output log is running!\n");
    env.errorLog.printf("Error log is running!  Hooray!\n");
    std::cout << env.x << std::endl;
}
