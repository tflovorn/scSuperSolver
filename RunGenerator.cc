#include "RunGenerator.hh"

RunGenerator::RunGenerator() : 
    config(ConfigData()), label(std::string("")) {
}

RunGenerator::RunGenerator(const std::string& cfgFileName): 
    config(ConfigData(cfgFileName)), label(std::string(cfgFileName)) {
}

RunGenerator::~RunGenerator() {
    delete config;
    delete label;
}

RunGenerator::getLabel() {
    return label;
}

RunGenerator::setLabel(const std::string& newLabel) {
    label = newLabel;
}
