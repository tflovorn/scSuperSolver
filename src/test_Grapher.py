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

import sys, os

from Grapher import Grapher

if len(sys.argv) < 2:
    print "usage: python test_Grapher.py path"
    sys.exit(1)
path = sys.argv[1]

configNames = ["test_grapher0", "test_grapher1", "test_grapher2"]
fullConfigPaths = [os.path.join(path, config) for config in configNames]
graph = Grapher(fullConfigPaths)
outputs = graph.readOutputs()
for dataSet in outputs:
    print (dataSet.getLatestVar("config", "x") + " : " +
           dataSet.getLatestVar("test_section", "y"))

fig, axes = graph.simple2D("config", "x", "test_section", "y")
figurePath = os.path.join(path, "testFig")
graph.saveFigure(fig, figurePath)
