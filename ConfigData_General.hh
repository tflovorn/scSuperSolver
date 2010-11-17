#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <string>
#include <map>

class ConfigData {
public:
    // build empty ConfigData
    ConfigData();
    // initialize ConfigData with information from file
    ConfigData(const std::string& cfgFileName);
    // need to destroy the map
    ~ConfigData();
    // copy/assignment constructors should probably be written

    // read data from given file
    readFromFile(const std::string& cfgFileName);
    // write current data out to file
    writeToFile(const std::string& cfgFileName);
    // get named value from the map
    template <class DataType>
    DataType getValue(const std::string& key);
    // put a value into the map
    template <class DataType>
    void setValue(const std::string& key, DataType value);
private:
    // holds key/value pairs this ConfigData has seen
    std::map<std::string, std::string> cfgMap;
};

#endif
