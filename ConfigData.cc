#include "ConfigData.hh"

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
    for (it = lines->begin(); it != lines->end(); it++) {
        line = *it;
        size_t split = line.find(',');
        if (split != std::string::npos) {
            key = line.substr(0, split);
            value = line.substr(split + 1, line.length() - split - 1);
            setValue(key, value);
            std::cout << "adding key = " << key 
                << ", value = " << value << std::endl;
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
