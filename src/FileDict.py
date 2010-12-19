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
    
    def setGlobal(self, key, value):
        self.topDict[None][0][key] = value

    def getGlobal(self, key):
        return self.topDict[None][0][key]
    
    def getLatestVar(self, section, key):
        return self.topDict[section][-1][key]

    def readFromFile(self, filePath):
        """Read data from specified file into topDict."""
        
        fp = open(filePath, 'r')
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

    def writeToFile(self, filePath):
        """Write out topDict in proper format to specified file."""
        fp = open(filePath, 'w')
        for sectionName, section in self.topDict.items():
            # section = list of dicts
            for iteration in section:
                if sectionName != None: # global section has no name
                    fp.write("<begin>," + sectionName + "\n")
                for key, value in iteration.items():
                    fp.write(key + ',' + value + "\n")
                if sectionName != None:
                    fp.write("<end>," + sectionName + "\n")
        fp.close()

def readReferencedDict(initialFilePath, nameKey, section=None):
    config = FileDict(initialFilePath)
    configDirectory = os.path.split(initialFilePath)[0]
    if section == None:
        outputName = config.getGlobal(nameKey)
    else:
        outputName = config.getLatestVar(section, nameKey)
    outputPath = os.path.join(configDirectory, outputName)
    return FileDict(outputPath)
