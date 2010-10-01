#include "ConfigData.h"

const ConfigData& ConfigData::makeFromFile(const std::string& cfgFileName) {
    ConfigData const *cfg = new ConfigData(cfgFileName);
    return (const ConfigData&)(*cfg);
}

ConfigData::ConfigData(const std::string& cfgFileName) {
    // todo: need to handle case of readInputFile throwing exception
    std::ifstream cfgFile(cfgFileName.c_str());
    readConfigData(&cfgFile);
    cfgFile.close();
}

void ConfigData::readConfigData(std::ifstream *cfgFile) {
    
}

std::string readNext(std::ifstream *cfgFile) {

}
