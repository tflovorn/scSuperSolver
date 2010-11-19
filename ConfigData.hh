#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <fstream>
#include <boost/lexical_cast.hpp>

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<std::string> StringVector;

class ConfigData {
public:
    // build empty ConfigData
    ConfigData();
    // need to destroy the map
    ~ConfigData();
    // copy/assignment constructors should probably be written

    // read data from given file
    void readFromFile(const std::string& cfgFileName);
    // write current data out to file
    void writeToFile(const std::string& cfgFileName);
    // get named value from the map
    template <class DataType>
    DataType getValue(const std::string& key) const;
    // put a value into the map
    template <class DataType>
    void setValue(const std::string& key, DataType value);
private:
    // holds key/value pairs this ConfigData has seen
    StringMap *cfgMap;
    // get lines from config file, ignoring comments
    StringVector* readLines(const std::string& cfgFileName);
    // return true if line starts with '#', false otherwise
    bool isComment(const std::string& line);
};

// thrown by getValue
class KeyNotFoundException : public std::exception {
    virtual const char* what() const throw() {
        return "Key not found in map.";
    }
};

// getValue/setValue are implemented here because linking fails if they're
// implemented in the .cc file
template <class DataType>
DataType ConfigData::getValue(const std::string& key) const {
    StringMap::iterator it = cfgMap->find(key);
    if (it == cfgMap->end()) {
        throw new KeyNotFoundException();
    }
    return boost::lexical_cast<DataType>(it->second);
}

template <class DataType>
void ConfigData::setValue(const std::string& key, DataType value) {
    const std::string& strValue = boost::lexical_cast<std::string>(value);
    (*cfgMap)[key] = strValue;
}

#endif
