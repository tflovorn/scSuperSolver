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

import os, sys

if len(sys.argv) < 2:
    print "usage: python runTest.py testName"
    sys.exit(1)
testName = sys.argv[1]

path = os.getcwd()
testDataPath = os.path.join(path, "test_data")
sourcePath = os.path.join(path, "src")
testPath = os.path.join(sourcePath, testName)

extension = testName.split(".")[-1]
if extension == "py":
    status = os.spawnlp(os.P_WAIT, "python", "python", testPath, testDataPath)
elif extension == "out":
    status = os.spawnl(os.P_WAIT, testPath, testPath, testDataPath)
else:
    print "File type not recognized."
    sys.exit(1)

print "Test exit status: " + str(status)
