#include <iostream>

#include "Environment.hh"
#include "ConfigData.hh"
#include "State.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName = "test_cfg";
    const ConfigData& cfg = ConfigData::makeFromFile(cfgFileName);
    const Environment& env(cfg);
    State st(env);
    std::cout << st.getD1() << std::endl;
    std::cout << st.getEpsilonMin() << std::endl;
    std::cout << st.absErrorD1() << std::endl;
    std::cout << st.absErrorMu() << std::endl;
    std::cout << st.absErrorF0() << std::endl;
}
