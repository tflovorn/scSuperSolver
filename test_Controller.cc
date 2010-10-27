#include <cassert>

#include "Controller.hh"

int main(int argc, char *argv[]) {
    Controller& myControl = Controller::makeController("test_cfg");
    myControl.logConfig();
    bool success = myControl.selfConsistentCalc();
    myControl.logState();
    assert(success);
    return 0;
}
