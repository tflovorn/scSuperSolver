#include "ConfigData.h"

const ConfigData& ConfigData::makeFromFile(const std::string& fname) {
    ConfigData const *cfg = new ConfigData(fname);
    return (const ConfigData&)(*cfg);
}

ConfigData::ConfigData(const std::string& fname) {
    // todo: need to handle case of readInputFile throwing exception
    std::ifstream cfgFile(fname.c_str());
    readConfigData(&cfgFile);
    cfgFile.close();
}

void ConfigData::readConfigData(std::ifstream *cfgFile) {
    
}
