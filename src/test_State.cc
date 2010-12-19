/*
  Copyright (c) 2010 Timothy Lovorn

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <iostream>

#include "Environment.hh"
#include "ConfigData.hh"
#include "State.hh"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: test_State.out path" << std::endl;
    }
    const std::string& cfgFileName = "test_cfg",
                       path = argv[1];
    ConfigData *cfg = new ConfigData(path, cfgFileName);
    Environment *env = new Environment(*cfg);
    State st(*env);
    st.makeSelfConsistent();
    std::cout << "D1: " << st.getD1() << " error: " 
        << st.absErrorD1() << std::endl;
    std::cout << "mu: " << st.getMu() << " error: " 
        << st.absErrorMu() << std::endl;
    std::cout << "F0: " << st.getF0() << " error: " 
         <<st.absErrorF0() << std::endl;
    std::cout << st.getEpsilonMin() << std::endl;
}
