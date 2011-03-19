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

#ifndef __SCSS_INTEGRATOR_HH
#define __SCSS_INTEGRATOR_HH

#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#include "Logger.hh"

#define WS_SIZE 10000 // size allocated for gsl workspace

class Integrator {
public:
    Integrator(double (*const integrand)(double, void*), void * const params,
               double _absTolerance, double _relTolerance);
    ~Integrator();
    double doIntegral(double leftBound, double rightBound, 
                      const Logger& errorLog);
private:
    gsl_function myFunction;
    gsl_integration_workspace *myWorkspace;
    double absTolerance, relTolerance;
};

#endif
