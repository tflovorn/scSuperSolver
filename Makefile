all: test_Logger.out test_ConfigData.out test_Environment.out test_State.out \
test_BZone.out

clean:
	\rm -f *.gch *.o *.out test_ConfigData_out test_ConfigData_err test_Logger_log

OBJS = Logger.o ConfigData.o Environment.o State.o BZone.o

test_Logger.out: test_Logger.o $(OBJS)
	g++ -o test_Logger.out test_Logger.o $(OBJS)

test_ConfigData.out: test_ConfigData.o $(OBJS)
	g++ -o test_ConfigData.out test_ConfigData.o $(OBJS)

test_Environment.out: test_Environment.o $(OBJS)
	g++ -o test_Environment.out test_Environment.o $(OBJS)

test_State.out: test_State.o $(OBJS)
	g++ -o test_State.out test_State.o $(OBJS)

test_BZone.out: test_BZone.o $(OBJS)
	g++ -o test_BZone.out test_BZone.o $(OBJS)

test_Logger.o: test_Logger.cc Logger.hh
	g++ -c test_Logger.cc

test_ConfigData.o: test_ConfigData.cc ConfigData.hh
	g++ -c test_ConfigData.cc

test_Environment.o: test_Environment.cc Environment.hh
	g++ -c test_Environment.cc

test_State.o: test_State.cc State.hh
	g++ -c test_State.cc

test_BZone.o: test_BZone.cc BZone.hh State.hh
	g++ -c test_BZone.cc

Logger.o: Logger.cc Logger.hh
	g++ -c Logger.cc

ConfigData.o: ConfigData.cc ConfigData.hh
	g++ -c ConfigData.cc

Environment.o: Environment.cc Environment.hh
	g++ -c Environment.cc

State.o: State.cc State.hh
	g++ -c State.cc

BZone.o: BZone.cc BZone.hh State.hh
	g++ -c BZone.cc

Environment.hh: ConfigData.hh Logger.hh

State.hh: Environment.hh
