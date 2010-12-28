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
#include <cmath>
#include <cassert>

#include "ConfigData.hh"
#include "ZeroTempEnvironment.hh"
#include "ZeroTempState.hh"
#include "BZone.hh"

double test_1(const ZeroTempState& st, double kx, double ky) {
    return 1.0;
}

double test_sin(const ZeroTempState& st, double kx, double ky) {
    return sin(kx) + sin(ky);
}

double test_step(const ZeroTempState& st, double kx, double ky) {
    if (kx > 0 && ky > 0) {
        return -1;
    }
    else {
        return 1;
    } 
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: test_BZone.out path" << std::endl;
    }
    std::cout << "Starting BZone test." << std::endl;
    const std::string& cfgFileName = "test_cfg",
                       path = argv[1];
    ConfigData *cfg = new ConfigData(path, cfgFileName);
    ZeroTempEnvironment *env = new ZeroTempEnvironment(*cfg);
    ZeroTempState* st_pt = new ZeroTempState(*env);
    ZeroTempState st = *st_pt;

    double avg_1 = BZone::average<ZeroTempState>((const BaseState&)st, 
        (const ZeroTempState&)st, test_1);
    assert(avg_1 == 1);
    std::cout << "avg_1 = " << avg_1 << std::endl;

    double sin_tol = 1e-17;
    double avg_sin = BZone::average<ZeroTempState>((const BaseState&)st, 
        (const ZeroTempState&)st, test_sin);
    assert(avg_sin < sin_tol);
    std::cout << "avg_sin = " << avg_sin << std::endl;

    double min_step = BZone::minimum<ZeroTempState>((const BaseState&)st, 
        (const ZeroTempState&)st, test_step);
    assert(min_step == -1);
    std::cout << "min_step = " << min_step << std::endl;

    return 0;
}
