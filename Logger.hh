#ifndef __MFTS_LOGGER_H
#define __MFTS_LOGGER_H

#include <string>
#include <cstdarg>
#include <cstdio>

class Logger {
public:
    // This constructor opens file for writing with given name.
    // Destructor should close this file.
    Logger(const std::string& fname);
    // Destructor.
    ~Logger();
    // Client calls this to write to our open stream.
    void printf(const std::string& format, ...) const;
private:
    // Stream we'll write to.
    FILE *myLog;
};

#endif
