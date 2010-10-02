all: test_Logger.out test_ConfigData.out test_Environment.out test_State.out

clean:
	\rm *.o *.gch *.out test_ConfigData_out test_ConfigData_err test_Logger_log

test_Logger.out: test_Logger.o Logger.o
	g++ -o test_Logger.out test_Logger.o Logger.o

test_ConfigData.out: test_ConfigData.o ConfigData.o
	g++ -o test_ConfigData.out test_ConfigData.o ConfigData.o

test_Environment.out: test_Environment.o Environment.o ConfigData.o Logger.o
	g++ -o test_Environment.out test_Environment.o Environment.o ConfigData.o Logger.o

test_State.out: test_State.o State.o Environment.o ConfigData.o Logger.o
	g++ -o test_State.out test_State.o State.o Environment.o ConfigData.o Logger.o

test_Logger.o: test_Logger.cc Logger.hh
	g++ -c test_Logger.cc

test_ConfigData.o: test_ConfigData.cc ConfigData.hh
	g++ -c test_ConfigData.cc

test_Environment.o: test_Environment.cc Environment.hh
	g++ -c test_Environment.cc

test_State.o: test_State.cc State.hh
	g++ -c test_State.cc

Logger.o: Logger.cc Logger.hh
	g++ -c Logger.cc

ConfigData.o: ConfigData.cc ConfigData.hh
	g++ -c ConfigData.cc

Environment.o: Environment.cc Environment.hh
	g++ -c Environment.cc

State.o: State.cc State.hh
	g++ -c State.cc

Environment.hh: ConfigData.hh Logger.hh

State.hh: Environment.hh
