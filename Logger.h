#ifndef __MFTS_LOGGER_H
#define __MFTS_LOGGER_H

#include <iostream>
#include <string>

class Logger {
public:
    // This constructor opens file for writing with given name.
    // Destructor should close this file.
    Logger(const std::string& fname);
    // This constructor captures given output stream.
    // Not responsible for closing it.
    Logger(std::ostream& log);
    // Destructor.
    ~Logger();
    // Client calls this to write to stream, doesn't care what that stream is.
    void write(const std::string& outData);
private:
    // Stream we'll write to.
    std::ostream& myLog;
    // Does the destructor need to close the stream?
    const bool closeStream;
};

#endif
