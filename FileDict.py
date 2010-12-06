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

class FileDict(object):
    """Dictionary of lists of dictionaries.
       
    topDict has key = section name, value = list of dictionaries
    keys outside of any section are put in section with key=None
    section's list of dictionaries are ordered by their ocurrence in file

    special characters (these shouldn't be used in keys or values):
        , < > #

    example file:
    ---------------------
    gk1,gv1
    <begin>,s1
    k1,v1
    k2,v2
    <end>,s1
    # this is a comment
    <begin>,s1
    v3,v3
    <end>,s1
    <begin>,s2
    k4,v4
    <end>,s2
    ---------------------
    reading this file results in the following structure for topDict:
    {None: [{gk1: gv1}],
     s1: [{k1: v1, k2: v2}, {k3: v3}],
     s2: [{k4: v4}]}

    """
    
    def __init__(self, fileName=None):
        self.topDict = {None: [{}]}
        if fileName != None:
            self.readFromFile(str(fileName))

    def readFromFile(self, fileName):
        fp = open(fileName, 'r')
        lines = fp.readlines()
        fp.close()
        sectionName = None
        for line in lines:
            # ignore leading/trailing whitespace
            line = line.strip()

            # if line is a comment, skip it
            if line[0] == "#":
                continue

            # assume there is only one comma in the line
            parts = line.split(',')
            key, value = parts[0], parts[1]

            # if line is a section change, handle it
            if key == "<begin>":
                # must be outside a section to start a new one
                if sectionName != None:
                    raise ValueError("File in improper format:"
                                     "<begin> outside global section.")
                # make entry for new dict
                sectionName = value
                if sectionName in self.topDict:
                    self.topDict[sectionName].append({})
                else:
                    self.topDict[sectionName] = [{}]
                continue
            if key == "<end>":
                # must be inside a section to leave it
                if sectionName == None:
                    raise ValueError("File in improper format:"
                                     "<end> in global section.")
                sectionName = None
                continue

            # line isn't special, add it to dict
            self.topDict[sectionName][-1][key] = value

    def writeToFile(self, fileName):
        fp = open(fileName, 'w')
        for sectionName, section in self.topDict.items():
            for iteration in section:
                if sectionName != None:
                    fp.write("<begin>," + sectionName + "\n")
                for key, value in iteration.items():
                    fp.write(key + ',' + value + "\n")
                if sectionName != None:
                    fp.write("<end>," + sectionName + "\n")
        fp.close()
