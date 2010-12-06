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

import os

DEFAULT_MAX_PROCESSES = 2
DEFAULT_CONTROLLER_NAME = "mainController.out"

class ControllerQueue(object):
    def __init__(self, initialQueue=None, 
                 controllerName=DEFAULT_CONTROLLER_NAME,
                 maxProcesses=DEFAULT_MAX_PROCESSES):
        self.maxProcesses = maxProcesses
        self.controllerName = controllerName
        if initialQueue == None:
            self.queue = []
        else:
            self.queue = initialQueue

    def enqueue(self, newConfig):
        self.queue.append(newConfig)

    def enqueueList(self, newConfigList):
        self.queue.extend(newConfigList)

    def runAll(self):
        pids = []
        while len(self.queue) > 0:
            pid = os.spawnl(os.P_NOWAIT, self.controllerName, 
                            self.controllerName, self.queue[0])
            pids.append(pid)
            self.queue = self.queue[1:]
            while len(pids) >= self.maxProcesses:
                os.waitpid(pids[0], 0)
                pids = pids[1:]
