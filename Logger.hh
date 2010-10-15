#ifndef __MFTS_LOGGER_H
#define __MFTS_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger {
public:
    // This constructor opens file for writing with given name.
    // Destructor should close this file.
    Logger(const std::string& fname);
    // Destructor.
    ~Logger();
    // Client calls this to write to our open stream.
    void write(const std::string& outData) const;
    void writeln(const std::string& outData) const;
private:
    // Stream we'll write to.
    std::ofstream *myLog;
};

#endif
