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

# -- Grapher stuff doesn't really belong here, new object to combine these? --

from RunInterface import RunInterface
from Grapher import Grapher

if len(sys.argv) < 2:
    print "usage: python test_RunInterface.py path"
    sys.exit(1)
path = sys.argv[1]

testRunInterface = RunInterface(path, "test_cfg")
testConfigs = testRunInterface.oneDimRun("test_xrun", "x", 0.04, 0.18, 0.04)
testRunInterface.doRun(testConfigs, maxProcesses=4)

grapher = Grapher(testConfigs)
fig, axes = grapher.simple2D("config", "x", "state", "f0")
grapher.setAxisLabels(axes, "x", "F0")
figurePath = os.path.join(path, "test_F0")
grapher.saveFigure(fig, figurePath)
