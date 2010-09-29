#ifndef __MFTS_CONFIG_DATA_H
#define __MFTS_CONFIG_DATA_H

#include <string>
#include <iostream>
#include <fstream>

class ConfigData {
public:
    // Create a ConfigData from file with given name, returning const ref
    static const ConfigData& makeFromFile(const std::string& fname);
    // Destructor checks fileOpen and will close myInput if true, 
    // so we know the file will get closed even if an exception is thrown.
    ~ConfigData();
    // Parameters for Environment to scoop up (descriptions in Environment.h)
    std::string label;
    double gridLen, t0, tz, thp, x, th, alpha, initD1, initMu, initF0,
           tolD1, tolMu, tolF0;
private:
    std::ifstream *myInput;
    bool fileOpen;
    // Constructor handles opening and (normally) closing file.
    ConfigData(const std::string& fname);
    // Read data from myInput and store it.
    void readInputFile();
};

#endif
