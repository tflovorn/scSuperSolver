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

DEFAULT_CONTROLLER_NAME = "mainController.out"

class ControllerQueue(object):
    """Queue which handles spawning of new controllers.

    Input one more more configs through __init__/enqueue/enqueueList.
    Call runAll when ready to run controllers.

    """
    def __init__(self, initialQueue, maxProcesses,
                 controllerName=DEFAULT_CONTROLLER_NAME):
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
        """Spawn a controller for all configs in queue.

        Number of simultaneous processes is no more than maxProcesses.
        This uses Unix-specific functionality! (os.wait)

        """
        if not os.path.exists(self.controllerName):
            raise Exception("Controller doesn't exist!")

        pids = []
        while len(self.queue) > 0:
            path, configName = os.path.split(self.queue[0])
            pid = os.spawnl(os.P_NOWAIT, self.controllerName, 
                            self.controllerName, path, configName)
            pids.append(pid)
            self.queue = self.queue[1:]
            # if we have enough processes now, we need to wait
            while len(pids) >= self.maxProcesses:
                donePid, status = os.wait()
                pids.remove(donePid)
        # wait for any remaining processes to finish
        while len(pids) > 0:
            donePid, status = os.wait()
            pids.remove(donePid)
