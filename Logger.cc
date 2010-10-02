#include "Logger.hh"

Logger::Logger(const std::string& fname) { 
    myLog = new std::ofstream(fname.c_str());
}

Logger::~Logger() {
    myLog->close();
    delete myLog;
}

void Logger::write(const std::string& outData) const {
    (*myLog) << outData << std::endl;
    (*myLog).flush();
}
