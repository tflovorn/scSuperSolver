#include <iostream>

#include "Environment.hh"
#include "ConfigData.hh"
#include "State.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName = "test_cfg";
    ConfigData *cfg = new ConfigData();
    cfg->readFromFile(cfgFileName);
    const Environment& env((const ConfigData&)cfg);
    State st(env);
    st.makeSelfConsistent();
    std::cout << "D1: " << st.getD1() << " error: " 
        << st.absErrorD1() << std::endl;
    std::cout << "mu: " << st.getMu() << " error: " 
        << st.absErrorMu() << std::endl;
    std::cout << "F0: " << st.getF0() << " error: " 
         <<st.absErrorF0() << std::endl;
    std::cout << st.getEpsilonMin() << std::endl;
}
