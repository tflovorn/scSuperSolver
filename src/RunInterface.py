# Copyright (c) 2010, 2011 Timothy Lovorn
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
from ControllerQueue import ControllerQueue
from Grapher import Grapher

DEFAULT_MAX_PROCESSES = 2

niceLabels = {"d1": "$D_{1}$", "mu": "$\mu$", "f0": "$F_{0}$", "x": "$x$"}

class RunInterface(object):
    def __init__(self, path):
        self.path = path

    def doRun(self, configFiles, maxProcesses=DEFAULT_MAX_PROCESSES):
        """Run a controller for each config in configFiles."""
        queue = ControllerQueue(configFiles, maxProcesses)
        queue.runAll()

    def graphData(self, configFiles, xVar, yVar, outputName):
        grapher = Grapher(configFiles)
        fig, axes = grapher.simple2D("config", xVar, "state", yVar)
        grapher.setAxisLabels(axes, self.label(xVar), self.label(yVar))
        figurePath = os.path.join(self.path, outputName)
        grapher.saveFigure(fig, figurePath)
        return fig, axes

    def label(self, var):
        if var in niceLabels:
            return niceLabels[var]
        else:
            return var

    def makeRun(self, baseConfig, runData):
        """Make a new run of config files from the base config and runData.

        runData is a list of tuples which contain a label and a dict.
        Labels are used to name generated configs and their specified output 
        files.  The dicts are key-value pairs for data to modify in the
        base config.  Return a list of the names of config files generated.

        """
        configNames = []
        baseConfigFullPath = os.path.join(self.path, baseConfig)
        for label, labelData in runData:
            newConfig = FileDict(baseConfigFullPath)
            newConfigFullPath = os.path.join(self.path, label + "_config")
            labelData.update({"outputLogName" : label + "_out.fd",
                              "errorLogName" : label + "_error",
                              "debugLogName" : label + "_debug"})
            for key, value in labelData.items():
                newConfig.setGlobal(str(key), str(value))
            configNames.append(newConfigFullPath)
            newConfig.writeToFile(newConfigFullPath)
        return configNames

    def oneDimRun(self, baseConfig, label, varName, minimum, maximum, step):
        """One-dimensional run with varName from [minimum, maximum).

        Returns names of config files.

        """
        index = 0
        varValue = minimum
        runData = []
        while varValue < maximum:
            runData.append((label + "_" + str(index) + "_", 
                           {varName : varValue}))
            varValue += step
            index += 1
        return self.makeRun(baseConfig, runData)

    def multiDimRun(self, baseConfig, label, varDataList):
        configs = []
        for index, data in enumerate(varDataList):
            varName, minimum, maximum, step = data
            if len(configs) == 0:
                label += "_%s_" % varName
                configs = self.oneDimRun(baseConfig, label, 
                                         varName, minimum, maximum, step)
            else:
                newConfigs = []
                label += "_%s_" % varName
                for index, some_config in enumerate(configs):
                    newConfigs.extend(self.oneDimRun(some_config, 
                                       label + "_" + str(index) + "_",
                                       varName, minimum, maximum, step))
                configs = newConfigs
        return configs
