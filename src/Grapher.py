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
