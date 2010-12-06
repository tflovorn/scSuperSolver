#############################################################################
# Copyright (C) 2010 Tim Lovorn
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

class RunInterface(object):
    def __init__(self, baseConfigName):
        self.baseConfigName = baseConfigName

    def doRun(self, configFiles):
        queue = ControllerQueue(configFiles)
        queue.runAll()

    def makeRun(self, runsData):
        """Make a new run of config files from the base config and runData.

        runDict is a dict of dicts.  keys in runDict are label for each run;
        the associated dicts are key-value pairs for data to modify in the
        base config.  Return names of config files.

        """
        configNames = []
        for label, labelData in runsData.items():
            newConfig = FileDict(baseConfigName)
            labelData.update({"outputLogName" : label + "_out.fd",
                              "errorLogName" : label + "_error",
                              "debugLogName" : label + "_debug"})
            for key, value in labelData.items():
                newConfig.setGlobal(key, value)
            newConfigName = label + "_config"
            configNames.append(newConfigName)
            newConfig.writeToFile(newConfigName)
        return configNames
