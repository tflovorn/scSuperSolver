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

#include "ConfigData.hh"

ConfigData::ConfigData(const std::string& _path) : path(_path) {
    cfgMap = new StringMap();
}

ConfigData::ConfigData(const std::string& _path, 
                       const std::string& cfgFileName) : path(_path) {
    cfgMap = new StringMap();
    readFromFile(cfgFileName);
}

ConfigData::~ConfigData() {
    delete cfgMap;
}

ConfigData::ConfigData(const ConfigData& conf) {
    cfgMap = conf.cfgMap;
    path = conf.path;
}

ConfigData& ConfigData::operator=(const ConfigData& conf) {
    delete cfgMap;
    cfgMap = conf.cfgMap;
    path = conf.path;
}

void ConfigData::readFromFile(const std::string& cfgFileName) {
    StringVector *lines = readLines(Utility::joinPath(path, cfgFileName));
    StringVector::iterator it;
    std::string line, key, value;
    for (it = lines->begin(); it != lines->end(); it++) {
        line = *it;
        size_t split = line.find(',');
        if (split != std::string::npos) {
            key = line.substr(0, split);
            value = line.substr(split + 1, line.length() - split - 1);
            setValue(key, value);
        }
    }
    delete lines;
}

void ConfigData::writeToFile(const std::string& cfgFileName) const {
    std::string fullPath = Utility::joinPath(path, cfgFileName);
    StringMap::iterator it;
    std::ofstream ofs(fullPath.c_str());
    for (it = cfgMap->begin(); it != cfgMap->end(); it++) {
        std::string line = (*it).first + "," + (*it).second + "\n";
        ofs.write(line.c_str(), line.length());
    }
    ofs.close();
}

void ConfigData::writeToLog(const Logger& log) const {
    StringMap::iterator it;
    log.printf("<begin>,config\n");
    for (it = cfgMap->begin(); it != cfgMap->end(); it++) {
        log.printf("%s,%s\n", (*it).first.c_str(), (*it).second.c_str());
    }
    log.printf("<end>,config\n");
}

StringVector* ConfigData::readLines(const std::string& fullPath) {
    StringVector* lines = new StringVector();
    std::ifstream ifs(fullPath.c_str());
    std::string line;
    while (ifs.good()) {
        std::getline(ifs, line);
        if (!isComment(line)) {
            lines->push_back(line);
        }
    }
    return lines;
}

const std::string& ConfigData::getPath() const {
    return (const std::string&)path;
}

bool ConfigData::isComment(const std::string& line) {
    if (line[0] == '#') {
        return true;
    }
    else {
        return false;
    }
}
