#include "ConfigData.h"

const ConfigData& ConfigData::makeFromFile(const std::string& cfgFileName) {
    ConfigData const *cfg = new ConfigData(cfgFileName);
    return (const ConfigData&)(*cfg);
}

ConfigData::ConfigData(const std::string& cfgFileName) {
    // todo: need to handle case of readInputFile throwing exception
    std::ifstream cfgFile(cfgFileName.c_str());
    readConfigData(&cfgFile);
    cfgFile.close();
}

void ConfigData::readConfigData(std::ifstream *cfgFile) {
    // log file names
    outputLogName = nextToken();
    errorLogName = nextToken();
    // integers
    gridLen = nextInt();
    alpha = nextInt();
    // doubles
    t0 = nextDouble();
    tz = nextDouble();
    thp = nextDouble();
    x = nextDouble();
    initD1 = nextDouble();
    initMu = nextDouble();
    initF0 = nextDouble();
    tolD1 = nextDouble();
    tolMu = nextDouble();
    tolF0 = nextDouble();
}

std::string ConfigData::nextToken(std::ifstream *cfgFile) {
    char nextc;                     // pull stream one character at a time
    char buffer[MAX_TOKEN_SIZE];    // holds the token
    int bufferIndex = 0;            // index to write to in buffer
    bool tokenDone = false;         // set to true when done building token
    while (cfgFile.good() && !tokenDone) {
        nextc = cfgFile.get();
        // comment; skip the rest of line. if we had token data, we're done building it.
        if (nextc == '#') { 
            if (bufferIndex > 0) {
                tokenDone = true;
            }
            while (cfgFile.good() && nextc != '\n') {
                nextc = cfgFile.get()
            }
            continue;
        }
        // newline. if we had token data, we're done.
        if (nextc == '\n' && bufferIndex > 0) {
            tokenDone = true;
        }
    }
}

int ConfigData::nextInt(std::ifstream *cfgFile) {
    return atoi(nextToken().c_str());
}

double ConfigData::nextDouble(std::ifstream *cfgFile) {
    return atof(nextToken().c_str());
}
