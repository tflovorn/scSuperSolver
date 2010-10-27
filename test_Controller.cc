#include <cassert>

#include "Controller.hh"

int main(int argc, char *argv[]) {
    Controller& myControl = Controller::makeController("test_cfg");
    myControl.logConfig();
    bool success = myControl.selfConsistentCalc();
    std::cout << "about to log state" << std::endl;
    myControl.logState();
    std::cout << "done logging state" << std::endl;
    assert(success);
    return 0;
}
