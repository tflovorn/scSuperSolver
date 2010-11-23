#include <iostream>

#include "ConfigData.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName("test_cfg");
    ConfigData *cfg = new ConfigData(cfgFileName);
    std::cout << cfg->getValue<int>("gridLen") << std::endl;
    std::cout << cfg->getValue<double>("tolD1") << std::endl;
    cfg->writeToFile(cfgFileName + std::string("_rewrite"));
    return 0;
}
