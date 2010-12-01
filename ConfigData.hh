/****************************************************************************
 * Copyright (C) 2010 Tim Lovorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

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

#include "Logger.hh"

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<std::string> StringVector;

class ConfigData {
public:
    // build empty cfgMap
    ConfigData();
    // build cfgMap, using given file
    ConfigData(const std::string& cfgFileName);
    // destroy cfgMap
    ~ConfigData();
    // copy/assignment constructors required to transfer map to new copy
    ConfigData(const ConfigData& conf);
    ConfigData& operator=(const ConfigData& conf);

    // read data from given file
    void readFromFile(const std::string& cfgFileName);
    // write current data out to file
    void writeToFile(const std::string& cfgFileName) const;
    // write to Logger using FileDict protocol
    void writeToLog(const Logger& log) const;
    // get named value from the map
    template <class DataType>
    DataType getValue(const std::string& key) const;
    // put a value into the map
    template <class DataType>
    void setValue(const std::string& key, const DataType& value);
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
void ConfigData::setValue(const std::string& key, const DataType& value) {
    const std::string& strValue = boost::lexical_cast<std::string>(value);
    (*cfgMap)[key] = strValue;
}

#endif
