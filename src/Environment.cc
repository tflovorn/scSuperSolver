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

#include "Environment.hh"

// Grab all the data from cfg.  Is there a less ugly way to do this?
// Also, need to make loggers.
Environment::Environment(const ConfigData& cfg) :
    gridLen(cfg.getValue<int>("gridLen")),
    t0(cfg.getValue<double>("t0")), 
    tz(cfg.getValue<double>("tz")),
    thp(cfg.getValue<double>("thp")),
    x(cfg.getValue<double>("x")),
    alpha(cfg.getValue<int>("alpha")),
    th(t0 * (1 - x)),  
    initD1(cfg.getValue<double>("initD1")),
    initMu(cfg.getValue<double>("initMu")),
    initF0(cfg.getValue<double>("initF0")),
    tolD1(cfg.getValue<double>("tolD1")),
    tolMu(cfg.getValue<double>("tolMu")),
    tolF0(cfg.getValue<double>("tolF0")),
    outputLog(cfg.getPath(), cfg.getValue<std::string>("outputLogName")),
    errorLog(cfg.getPath(), cfg.getValue<std::string>("errorLogName")),
    debugLog(cfg.getPath(), cfg.getValue<std::string>("debugLogName"))
{ }
