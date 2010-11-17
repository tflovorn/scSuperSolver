#include "ConfigData_General.hh"

ConfigData::ConfigData() {
    cfgMap = new StringMap();
}

ConfigData::~ConfigData() {
    delete cfgMap;
}

void ConfigData::readFromFile(const std::string& cfgFileName) {
    StringVector *lines = readLines(cfgFileName);
    StringVector::iterator it;
    std::string line, key, value;
    for (it = lines->begin(); it < lines->end(); it++) {
        line = *it;
        size_t split = line.find(',');
        if (split != std::string::npos) {
            key = line.substr(0, split);
            value = line.substr(split + 1, line.length() - split - 1);
            setValue(key, value);
        }
    }
}

void ConfigData::writeToFile(const std::string& cfgFileName) {
    StringMap::iterator it;
    std::ofstream ofs(cfgFileName.c_str());
    std::string line;
    for (it = cfgMap->begin(); it < cfgMap->end(); it++) {
        line = (*it)->first + "," + (*it)->second + "\n";
        ofs.write(line, line.length());
    }
    ofs.close();
}

template <class DataType>
DataType ConfigData::getValue(const std::string& key) {
    StringMap::iterator it = cfgMap->find(key);
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

StringVector* readLines(const std::string& cfgFileName) {
    StringVector* lines = new StringVector();
    std::ifstream ifs(cfgFileName.c_str());
    std::string line;
    while (ifs.good()) {
        std::getline(ifs, line);
        lines.push_back(line);
    }
    return lines;
}
