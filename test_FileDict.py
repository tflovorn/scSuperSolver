import FileDict

myDict = FileDict.FileDict("test_FileDict.fd")
print myDict.topDict
myDict.writeToFile("test_FileDict_rewrite.fd")
