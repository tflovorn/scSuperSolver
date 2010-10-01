#include "Logger.hh"

int main(int argc, char *argv[]) {
    Logger myLog = Logger("test_Logger_log");
    myLog.write("I love the power glove");
    myLog.write("It's so bad...");
}
