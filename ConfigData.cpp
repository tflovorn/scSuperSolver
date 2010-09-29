#include "ConfigData.h"

const ConfigData& ConfigData::makeFromFile(const std::string& fname) {
    ConfigData *cfg = new ConfigData(fname);
    return (const ConfigData&)(*cfg);
}

ConfigData::ConfigData(const std::string& fname) : fileOpen(false) {
    std::ifstream inFile;
    inFile.open(fname);
    if (inFile.is_open()) {
        fileOpen = true;
        myInput = &inFile;
        readInputFile();
        inFile.close();
        fileOpen = false;
    }   
}

void ConfigData::readInputFile() {

}

ConfigData::~ConfigData() {
    if (fileOpen == true) {
        myInput.close();
    }
}
