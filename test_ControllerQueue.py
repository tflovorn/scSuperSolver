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

import ControllerQueue

configList = ["test_cfg", "test_cfg2", "test_cfg3", "test_cfg4"]
testQueue = ControllerQueue.ControllerQueue(initialQueue=configList)
testQueue.runAll()
