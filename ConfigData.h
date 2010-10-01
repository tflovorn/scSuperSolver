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
    std::string cfgFileName, outputLogName, errorLogName;
    double gridLen, t0, tz, thp, x, th, alpha, initD1, initMu, initF0,
           tolD1, tolMu, tolF0;
private:
    // Constructor handles opening and (normally) closing file.
    ConfigData(const std::string& cfgFileName);
    // Read data from myInput and store it.
    void readConfigData(std::ifstream *cfgFile);
};

#endif
