#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

// tokens OR lines in config file can be this long at most (minus one character for \0)
#define MAX_TOKEN_SIZE 1000

class ConfigData {
public:
    // Create a ConfigData from file with given name, returning const ref
    static const ConfigData& makeFromFile(const std::string& cfgFileName);
    // Parameters for Environment to scoop up (descriptions in Environment.h)
    std::string outputLogName, errorLogName;
    int gridLen, alpha;
    double t0, tz, thp, x, th, initD1, initMu, initF0,
           tolD1, tolMu, tolF0;
private:
    // Constructor handles opening and (normally) closing file.
    ConfigData(const std::string& cfgFileName);
    // Read data from cfgFile and store it.
    void readConfigData(std::ifstream *cfgFile);
    // Helper for readConfigData, gives next valid token in stream
    // (i.e. not in a comment). does not convert to correct type!
    std::string nextToken(std::ifstream *cfgFile);
    // If token should be an integer
    int nextInt(std::ifstream *cfgFile);
    // If token should be a double
    double nextDouble(std::ifstream *cfgFile);
};

#endif
