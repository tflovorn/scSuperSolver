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

import os

from FileDict import FileDict

class Grapher(object):
    def __init__(self, configPaths):
        self.configPaths = configPaths

    def addConfigs(self, configPaths):
        self.configPaths.extend(configPaths)

    def readOutputs(self):
        configs = [FileDict(filePath) for filePath in self.configPaths]
        configDirectories = [os.path.split(filePath)[0] for 
                             filePath in self.configPaths]
        outputNames = [cfg.getGlobal("outputLogName") for cfg in configs]
        outputPaths = [os.path.join(front, back) for
                       front, back in zip(configDirectories, outputNames)]
        return [FileDict(outputFile) for outputFile in outputPaths]

    def simple2D(self, xSection, xVar, xLabel, ySection, yVar, yLabel):
        outputData = self.readOutputs()
