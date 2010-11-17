#include "ConfigData_General.hh"

ConfigData::ConfigData() {
    cfgMap = new StringMap();
}

ConfigData::~ConfigData() {
    delete cfgMap;
}

void readFromFile(const std::string& cfgFileName) {

}

void writeToFile(const std::string& cfgFileName) {

}

template <class DataType>
DataType ConfigData::getValue(const std::string& key) {
    StringMap::iterator it = cfgMap.find(key);
    if (it == std::map::end) {
        throw KeyNotFoundException;
    }
    return boost::lexical_cast<DataType>(it->second);
}

template <class DataType>
void ConfigData::setValue(const std::string& key, DataType value) {
    std::string strValue = boost::lexical_cast<std::string>(value);
    cfgMap[strValue] = key;
}
