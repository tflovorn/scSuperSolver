#include "ConfigData.h"

const ConfigData& ConfigData::makeFromFile(const std::string& fname) {
    ConfigData *cfg = new ConfigData(fname);
    return (const ConfigData&)(*cfg);
}

ConfigData::ConfigData(const std::string& fname) {
    std::ifstream cfgFile(fname.c_str());
    readConfigData(&cfgFile); // need to handle case of readInputFile throwing exception
    cfgFile.close();
}

void ConfigData::readConfigData(std::ifstream *cfgFile) {
    
}
