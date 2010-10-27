#include "Logger.hh"

Logger::Logger(const std::string& fname) { 
    myLog = fopen(fname.c_str(), "w");
}

Logger::~Logger() {
    fclose(myLog);
}

void Logger::printf(const std::string& fmt, ...) const {
    va_list args;
    va_start(args, fmt);
    vfprintf(myLog, fmt.c_str(), args);
    va_end(args);
}
