#include <iostream>
#include <string>

#include "Controller.hh"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: mainController.out cfgFileName" << std::endl;
        return 1;
    }
    const std::string& cfgFileName = argv[1];
    Controller& myControl = Controller::makeController(cfgFileName);
    myControl.selfConsistentCalc();
    myControl.logState();
    return 0;
}
