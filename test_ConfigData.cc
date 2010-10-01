#include <iostream>

#include "ConfigData.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName("test_ConfigData_cfg");
    const ConfigData& cfg = ConfigData::makeFromFile(cfgFileName);
    std::cout << cfg.gridLen << std::endl;
    std::cout << cfg.tolD1 << std::endl;
    return 0;
}
