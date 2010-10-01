#include "ConfigData.hh"

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
    // row 1: log file names
    outputLogName = nextToken();
    errorLogName = nextToken();
    // row 2: integer parameters
    gridLen = nextInt();
    alpha = nextInt();
    // row 3: float parameters
    t0 = nextDouble();
    tz = nextDouble();
    thp = nextDouble();
    x = nextDouble();
    // row 4: initialization values
    initD1 = nextDouble();
    initMu = nextDouble();
    initF0 = nextDouble();
    // row 5: tolerances
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
        // comment: skip the rest of line.
        // if we had token data, we're done building it.
        if (nextc == '#') { 
            if (bufferIndex > 0) {
                tokenDone = true;
            }
            while (cfgFile.good() && nextc != '\n') {
                nextc = cfgFile.get()
            }
            continue;
        }
        // newline or comma: token done.
        if ((nextc == '\n' || nextc == ',') && bufferIndex > 0) {
            tokenDone = true;
	        continue;
        }
    	// whitespace: move along
    	if (nextc == ' ' || nextc == '\t') {
	        continue;
    	}
        // good character: save it
        buffer[bufferIndex] = nextc;
        bufferIndex++;
    }
    buffer[bufferIndex] = '\0';
    return std::string(buffer);
}

// going from C string to std::string and back is a little silly
// but I would prefer to do that than have nextToken() return a C string
int ConfigData::nextInt(std::ifstream *cfgFile) {
    return atoi(nextToken().c_str());
}

double ConfigData::nextDouble(std::ifstream *cfgFile) {
    return atof(nextToken().c_str());
}
