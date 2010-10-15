#include "ConfigData.hh"

const ConfigData& ConfigData::makeFromFile(const std::string& cfgFileName) {
    ConfigData const *cfg = new ConfigData(cfgFileName);
    return (const ConfigData&)(*cfg);
}

ConfigData::ConfigData(const std::string& cfgFileName) {
    // TODO: need to handle case of readConfigData throwing exception
    std::ifstream cfgFile(cfgFileName.c_str());
    readConfigData(&cfgFile);
    cfgFile.close();
}

void ConfigData::readConfigData(std::ifstream *cfgFile) {
    // row 1: log file names
    outputLogName = nextToken(cfgFile);
    errorLogName = nextToken(cfgFile);
    // row 2: integer parameters
    gridLen = nextInt(cfgFile);
    alpha = nextInt(cfgFile);
    // row 3: float parameters
    t0 = nextDouble(cfgFile);
    tz = nextDouble(cfgFile);
    thp = nextDouble(cfgFile);
    x = nextDouble(cfgFile);
    // row 4: initialization values
    initD1 = nextDouble(cfgFile);
    initMu = nextDouble(cfgFile);
    initF0 = nextDouble(cfgFile);
    // row 5: tolerances
    tolD1 = nextDouble(cfgFile);
    tolMu = nextDouble(cfgFile);
    tolF0 = nextDouble(cfgFile);
}

std::string ConfigData::nextToken(std::ifstream *cfgFile) {
    char nextc;                     // pull stream one character at a time
    char buffer[MAX_TOKEN_SIZE];    // holds the token
    int bufferIndex = 0;            // index to write to in buffer
    bool tokenDone = false;         // set to true when done building token
    while (cfgFile->good() && !tokenDone) {
        nextc = cfgFile->get();
        // comment: skip the rest of line.
        // if we had token data, we're done building it.
        if (nextc == '#') { 
            if (bufferIndex > 0) {
                tokenDone = true;
            }
            while (cfgFile->good() && nextc != '\n') {
                nextc = cfgFile->get();
            }
            continue;
        }
        // newline or comma: token done.
        if ((nextc == '\n' || nextc == ',') && bufferIndex > 0) {
            tokenDone = true;
	        continue;
        }
    	// whitespace: move along. 
        // can check '\n' here only after checking it for token completion
    	if (nextc == ' ' || nextc == '\t' || nextc == '\n') {
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
    return atoi(nextToken(cfgFile).c_str());
}

double ConfigData::nextDouble(std::ifstream *cfgFile) {
    return atof(nextToken(cfgFile).c_str());
}
