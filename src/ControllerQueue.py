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
        if initialQueue is None:
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
