#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <string>
#include <iostream>
#include <fstream>

class ConfigData {
public:
    // Create a ConfigData from file with given name, returning const ref
    static const ConfigData& makeFromFile(const std::string& cfgFileName);
    // Parameters for Environment to scoop up (descriptions in Environment.h)
    std::string outputLogName, errorLogName;
    double t0, tz, thp, x, th, alpha, initD1, initMu, initF0,
           tolD1, tolMu, tolF0;
    int gridLen;
private:
    // Constructor handles opening and (normally) closing file.
    ConfigData(const std::string& cfgFileName);
    // Read data from cfgFile and store it.
    void readConfigData(std::ifstream *cfgFile);
    // Helper for readConfigData, gives next valid token in stream
    // (i.e. not in a comment)
    std::string readNext(std::ifstream *cfgFile);
};

#endif
