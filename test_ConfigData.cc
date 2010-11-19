#include <iostream>

#include "ConfigData.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName("test_cfg");
    ConfigData *cfg = new ConfigData();
    cfg->readFromFile(cfgFileName);
    std::cout << cfg->getValue<int>("gridLen") << std::endl;
    std::cout << cfg->getValue<double>("tolD1") << std::endl;
    return 0;
}
