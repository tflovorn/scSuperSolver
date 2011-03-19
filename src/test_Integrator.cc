/*
  Copyright (c) 2011 Timothy Lovorn

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

#include "Logger.hh"
#include "Integrator.hh"

// should converge to a value of x = 1
double test_integrator_linear(double x, void *params) {
    return x;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: test_Controller.out path" << std::endl;
    }
    const std::string& path = argv[1];
    Logger error(path, "test_error_log");
    Integrator integrator(&test_integrator_linear, NULL, 1e-6, 1e-6);
    double integral = integrator.doIntegral(0, 1.0, error);
    std::cout << integral << std::endl;
    return 0;
}
