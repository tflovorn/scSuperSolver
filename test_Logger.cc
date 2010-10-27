#include "Logger.hh"

int main(int argc, char *argv[]) {
    Logger myLog = Logger("test_Logger_log");
    myLog.printf("I love the power glove\n");
    myLog.printf("It's so bad...\n");
}
