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

import matplotlib.pyplot as plt

import FileDict

class Grapher(object):
    def __init__(self, configPaths):
        self.configPaths = configPaths

    def addConfigs(self, configPaths):
        self.configPaths.extend(configPaths)

    def readOutputs(self):
        return [FileDict.readReferencedDict(filePath, "outputLogName") for
                filePath in self.configPaths]

    def simple2D(self, xSection, xVar, ySection, yVar, fig=None, axes=None):
        # if either axes or figure is passed in as None, we ignore both
        if (fig is None) or (axes is None):
            fig = plt.figure()
            axes = fig.add_subplot(1,1,1)

        outputDataList = self.readOutputs()
        xData = [outputData.getLatestVar(xSection, xVar) 
                 for outputData in outputDataList]
        yData = [outputData.getLatestVar(ySection, yVar) 
                 for outputData in outputDataList]

        axes.plot(xData, yData, "k-")
        return fig, axes

    def setAxisLabels(self, axes, xLabel, yLabel):
        axes.set_xlabel(xLabel)
        axes.set_ylabel(yLabel)

    def saveFigure(self, fig, figurePath):
        fig.savefig(figurePath + ".png")
        fig.savefig(figurePath + ".eps")
