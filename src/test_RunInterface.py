# Copyright (c) 2010 Timothy Lovorn
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import os, sys

from RunInterface import RunInterface

if len(sys.argv) < 2:
    print "usage: python test_RunInterface.py path"
    sys.exit(1)
path = sys.argv[1]

interface = RunInterface(path, "test_cfg")
testConfigs = interface.oneDimRun("test_xrun", "x", 0.04, 0.18, 0.01)
interface.doRun(testConfigs, maxProcesses=4)

interface.graphData(testConfigs, "x", "d1", "test_d1")
interface.graphData(testConfigs, "x", "mu", "test_mu")
interface.graphData(testConfigs, "x", "f0", "test_f0")
