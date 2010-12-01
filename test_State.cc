/****************************************************************************
 * Copyright (C) 2010 Tim Lovorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

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
