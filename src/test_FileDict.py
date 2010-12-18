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

import sys, os

import FileDict

if len(sys.argv) < 2:
    print "usage: python test_FileDict.py path"
    sys.exit(1)
path = sys.argv[1]

myDict = FileDict.FileDict(os.path.join(path, "test_FileDict.fd"))
print myDict.topDict
myDict.writeToFile(os.path.join(path, "test_FileDict_rewrite.fd"))
