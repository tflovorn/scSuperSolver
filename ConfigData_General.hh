#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <string>
#include <map>
#include <exception>
#include "boost/lexical_cast.hpp"

typedef std::map<std::string, std::string> StringMap;

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
    DataType getValue(const std::string& key);
    // put a value into the map
    template <class DataType>
    void setValue(const std::string& key, DataType value);
private:
    // holds key/value pairs this ConfigData has seen
    StringMap *cfgMap;
};

// thrown by getValue
class KeyNotFoundException : public std::exception {
    virtual const char* what() const throw() {
        return "Key not found in map.";
    }
};

#endif
