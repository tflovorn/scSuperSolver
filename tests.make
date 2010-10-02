test_Logger.out: test_Logger.o Logger.o
	g++ -o test_Logger.out test_Logger.o Logger.o

test_ConfigData.out: test_ConfigData.o ConfigData.o
	g++ -o test_ConfigData.out test_ConfigData.o ConfigData.o

test_Logger.o: test_Logger.cc Logger.hh
	g++ -c test_Logger.cc

test_ConfigData.o: test_ConfigData.cc ConfigData.hh
	g++ -c test_ConfigData.cc

Logger.o: Logger.cc Logger.hh
	g++ -c Logger.cc

ConfigData.o: ConfigData.cc ConfigData.hh
	g++ -c ConfigData.cc
