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

#include "ConfigData.hh"

ConfigData::ConfigData() {
    cfgMap = new StringMap();
}

ConfigData::ConfigData(const std::string& cfgFileName) {
    cfgMap = new StringMap();
    readFromFile(cfgFileName);
}

ConfigData::~ConfigData() {
    delete cfgMap;
}

ConfigData::ConfigData(const ConfigData& conf) {
    cfgMap = conf.cfgMap;
}

ConfigData& ConfigData::operator=(const ConfigData& conf) {
    delete cfgMap;
    cfgMap = conf.cfgMap;
}

void ConfigData::readFromFile(const std::string& cfgFileName) {
    StringVector *lines = readLines(cfgFileName);
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

void ConfigData::writeToFile(const std::string& cfgFileName) {
    StringMap::iterator it;
    std::ofstream ofs(cfgFileName.c_str());
    std::string line;
    for (it = cfgMap->begin(); it != cfgMap->end(); it++) {
        line = (*it).first + "," + (*it).second + "\n";
        ofs.write(line.c_str(), line.length());
    }
    ofs.close();
}

StringVector* ConfigData::readLines(const std::string& cfgFileName) {
    StringVector* lines = new StringVector();
    std::ifstream ifs(cfgFileName.c_str());
    std::string line;
    while (ifs.good()) {
        std::getline(ifs, line);
        if (!isComment(line)) {
            lines->push_back(line);
        }
    }
    return lines;
}

bool ConfigData::isComment(const std::string& line) {
    if (line[0] == '#') {
        return true;
    }
    else {
        return false;
    }
}
