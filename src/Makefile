all: mainController.out

tests: test_Logger.out test_ConfigData.out test_ZeroTempEnvironment.out \
test_ZeroTempState.out test_BZone.out test_RootFinder.out test_Controller.out \
test_Utility.out

clean:
	\rm -f *.gch *.o *.out *.pyc *.pyo

OBJS = Logger.o ConfigData.o BaseEnvironment.o ZeroTempEnvironment.o \
BaseState.o ZeroTempState.o ZeroTempSpectrum.o RootFinder.o Controller.o \
Utility.o

FLAGS = -Wall -lgsl -lblas -I/usr/local/include/gsl/

mainController.out: mainController.o $(OBJS)
	g++ -o mainController.out mainController.o $(FLAGS) $(OBJS)

test_Logger.out: test_Logger.o $(OBJS)
	g++ -o test_Logger.out test_Logger.o $(FLAGS) $(OBJS)

test_ConfigData.out: test_ConfigData.o $(OBJS)
	g++ -o test_ConfigData.out test_ConfigData.o $(FLAGS) $(OBJS)

test_ZeroTempEnvironment.out: test_ZeroTempEnvironment.o $(OBJS)
	g++ -o test_ZeroTempEnvironment.out test_ZeroTempEnvironment.o $(FLAGS) $(OBJS)

test_ZeroTempState.out: test_ZeroTempState.o $(OBJS)
	g++ -o test_ZeroTempState.out test_ZeroTempState.o $(FLAGS) $(OBJS)

test_BZone.out: test_BZone.o $(OBJS)
	g++ -o test_BZone.out test_BZone.o $(FLAGS) $(OBJS)

test_RootFinder.out: test_RootFinder.o $(OBJS)
	g++ -o test_RootFinder.out test_RootFinder.o $(FLAGS) $(OBJS)

test_Controller.out: test_Controller.o $(OBJS)
	g++ -o test_Controller.out test_Controller.o $(FLAGS) $(OBJS)

test_Utility.out: test_Utility.o $(OBJS)
	g++ -o test_Utility.out test_Utility.o $(FLAGS) $(OBJS)

mainController.o: mainController.cc Controller.hh
	g++ -c mainController.cc

test_Logger.o: test_Logger.cc Logger.hh
	g++ -c test_Logger.cc

test_ConfigData.o: test_ConfigData.cc ConfigData.hh
	g++ -c test_ConfigData.cc

test_ZeroTempEnvironment.o: test_ZeroTempEnvironment.cc ZeroTempEnvironment.hh
	g++ -c test_ZeroTempEnvironment.cc

test_ZeroTempState.o: test_ZeroTempState.cc ZeroTempState.hh
	g++ -c test_ZeroTempState.cc

test_BZone.o: test_BZone.cc BZone.hh ZeroTempState.hh
	g++ -c test_BZone.cc

test_RootFinder.o: test_RootFinder.cc RootFinder.hh
	g++ -c test_RootFinder.cc

test_Controller.o: test_Controller.cc Controller.hh
	g++ -c test_Controller.cc

test_Utility.o: test_Utility.cc Utility.hh
	g++ -c test_Utility.cc

Logger.o: Logger.cc Logger.hh
	g++ -c Logger.cc

ConfigData.o: ConfigData.cc ConfigData.hh
	g++ -c ConfigData.cc

BaseEnvironment.o: BaseEnvironment.cc BaseEnvironment.hh
	g++ -c BaseEnvironment.cc

ZeroTempEnvironment.o: ZeroTempEnvironment.cc ZeroTempEnvironment.hh
	g++ -c ZeroTempEnvironment.cc

BaseState.o: BaseState.cc BaseState.hh
	g++ -c BaseState.cc

ZeroTempState.o: ZeroTempState.cc ZeroTempState.hh RootFinder.hh
	g++ -c ZeroTempState.cc

ZeroTempSpectrum.o: ZeroTempSpectrum.cc ZeroTempSpectrum.hh ZeroTempState.hh
	g++ -c ZeroTempSpectrum.cc

RootFinder.o: RootFinder.cc RootFinder.hh
	g++ -c RootFinder.cc $(FLAGS)

Controller.o: Controller.cc Controller.hh
	g++ -c Controller.cc

Utility.o: Utility.cc Utility.hh
	g++ -c Utility.cc

ConfigData.hh: Logger.hh Utility.hh

BaseEnvironment.hh: ConfigData.hh Logger.hh

ZeroTempEnvironment.hh: BaseEnvironment.hh

BaseState.hh: BaseEnvironment.hh

ZeroTempState.hh: BaseState.hh ZeroTempEnvironment.hh ZeroTempSpectrum.hh

Controller.hh: BaseState.hh ZeroTempState.hh
