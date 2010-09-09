#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <string>
#include <iostream>

class ConfigData {
public:
    // Constructor will trigger reading.
    ConfigData(std::ifstream& infs);
    // Destructor needed to close file.
    ~ConfigData();
    // Parameters for Environment to scoop up (descriptions in Environment.h)
    // We ASSUME these don't get messed with after reading.  Dangerous.
    std::string label;
    double gridLen, t0, tz, thp, x, th, alpha, initD1, initMu, initF0,
           tolD1, tolMu, tolF0;
private:
    // Input file stream, specified at construction.
    std::ifstream& myInput;
    // Read data from myInput and store it.
    void readInputFile();
};

#endif
