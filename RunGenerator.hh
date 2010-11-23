#ifndef __MFTS_RUN_GENERATOR_H
#define __MFTS_RUN_GENERATOR_H

#include <string>
#include <vector>
#include <cstdlib>

#include "ConfigData.hh"

class RunGenerator {
public:
    // make empty config
    RunGenerator();
    // initialize config with file
    RunGenerator(const std::string& cfgFileName);
    // destroy config
    ~RunGenerator();

    // Make a series of config files, with names = fileNameBase_varName_value.
    // Set key in config with name varName equal to set of values from
    // min to max using given step.
    // Config file output has other values as given in config.
    template <class DataType>
    int makeRun(const std::string& varName,
                const std::vector<DataType>& valueList);

    // set / get for label
    void setLabel(const std::string& newLabel);
    std::string& getLabel();

    // set key = value inside config
    template <class DataType>
    void setValue(const std::string& key, const DataType& value);
private:
    // handy representation of data
    ConfigData config;
    // gives beginning of file name
    std::string label;
};

template <class DataType>
int RunGenerator::makeRun(const std::string& varName, 
                          const std::vector<DataType>& valueList) {
    char *itoa(int i);
    std::vector<DataType>::const_iterator it;
    std::string fileName, nameBase = label + "_" + varName + "_";
    int runNumber = 0;

    for(it = valueList.begin(); it < valueList.end(); it++) {
        fileName = nameBase + std::string(itoa(runNumber));
        setValue<DataType>(varName, *it);
        config.writeToFile(fileName);
        runNumber++;
    }
    return runNumber;
}

template <class DataType>
void RunGenerator::setValue(const std::string& key, const DataType& value) {
    config.setValue<DataType>(key, value);
}

#endif
