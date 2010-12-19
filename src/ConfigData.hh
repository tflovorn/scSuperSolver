/*
  Copyright (c) 2010 Timothy Lovorn

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef __SCSS_CONFIG_DATA_H
#define __SCSS_CONFIG_DATA_H

#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "Utility.hh"
#include "Logger.hh"

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<std::string> StringVector;

class ConfigData {
public:
    // build empty cfgMap
    ConfigData(const std::string& _path);
    // build cfgMap, using given file
    ConfigData(const std::string& _path, const std::string& cfgFileName);
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
    // accessor for path
    const std::string& getPath() const;
private:
    // where the files live
    std::string path;
    // holds key/value pairs this ConfigData has seen
    StringMap *cfgMap;
    // get lines from config file, ignoring comments
    StringVector* readLines(const std::string& fullPath);
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
