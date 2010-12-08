#############################################################################
# Copyright (C) 2010 Timothy Lovorn
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################

from FileDict import FileDict
from ControllerQueue import ControllerQueue

DEFAULT_MAX_PROCESSES = 2

class RunInterface(object):
    def __init__(self, baseConfigName):
        self.baseConfigName = baseConfigName

    def doRun(self, configFiles, maxProcesses=DEFAULT_MAX_PROCESSES):
        """Run a controller for each config in configFiles."""
        queue = ControllerQueue(configFiles, maxProcesses)
        queue.runAll()

    def makeRun(self, runData):
        """Make a new run of config files from the base config and runData.

        runData is a list of tuples which contain a label and a dict.
        Labels are used to name generated configs and their specified output 
        files.  The dicts are key-value pairs for data to modify in the
        base config.  Return a list of the names of config files generated.

        """
        configNames = []
        for label, labelData in runData:
            newConfig = FileDict(self.baseConfigName)
            newConfigName = label + "_config"
            labelData.update({"outputLogName" : label + "_out.fd",
                              "errorLogName" : label + "_error",
                              "debugLogName" : label + "_debug"})
            for key, value in labelData.items():
                newConfig.setGlobal(str(key), str(value))
            configNames.append(newConfigName)
            newConfig.writeToFile(newConfigName)
        return configNames

    def oneDimRun(self, label, varName, minimum, maximum, step):
        """One-dimensional run with varName from [minimum, maximum).

        Returns names of config files.

        """
        index = 0
        varValue = minimum
        runData = []
        while varValue < maximum:
            runData.append((label + str(index), {varName : varValue}))
            varValue += step
            index += 1
        return self.makeRun(runData)
