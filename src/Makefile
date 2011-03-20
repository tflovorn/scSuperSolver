all: mainController.out

tests: test_Logger.out test_ConfigData.out test_ZeroTempEnvironment.out \
test_ZeroTempState.out test_BZone.out test_RootFinder.out test_Controller.out \
test_Utility.out test_Integrator.out

clean:
	\rm -f *.gch *.o *.out *.pyc *.pyo

OBJS = Logger.o ConfigData.o BaseEnvironment.o ZeroTempEnvironment.o \
BaseState.o ZeroTempState.o ZeroTempSpectrum.o PairTempEnvironment.o \
PairTempState.o PairTempSpectrum.o RootFinder.o Controller.o Utility.o \
Integrator.o CritTempEnvironment.o CritTempState.o CritTempSpectrum.o

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

test_Integrator.out: test_Integrator.o $(OBJS)
	g++ -o test_Integrator.out test_Integrator.o $(FLAGS) $(OBJS)

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

test_Integrator.o: test_Integrator.cc Integrator.hh
	g++ -c test_Integrator.cc

Logger.o: Logger.cc Logger.hh
	g++ -c Logger.cc

ConfigData.o: ConfigData.cc ConfigData.hh
	g++ -c ConfigData.cc

BaseEnvironment.o: BaseEnvironment.cc BaseEnvironment.hh
	g++ -c BaseEnvironment.cc

ZeroTempEnvironment.o: ZeroTempEnvironment.cc ZeroTempEnvironment.hh
	g++ -c ZeroTempEnvironment.cc

PairTempEnvironment.o: PairTempEnvironment.cc PairTempEnvironment.hh
	g++ -c PairTempEnvironment.cc

CritTempEnvironment.o: CritTempEnvironment.cc CritTempEnvironment.hh
	g++ -c CritTempEnvironment.cc

BaseState.o: BaseState.cc BaseState.hh
	g++ -c BaseState.cc

ZeroTempState.o: ZeroTempState.cc ZeroTempState.hh RootFinder.hh
	g++ -c ZeroTempState.cc

PairTempState.o: PairTempState.cc PairTempState.hh RootFinder.hh
	g++ -c PairTempState.cc

CritTempState.o: CritTempState.cc CritTempState.hh RootFinder.hh
	g++ -c CritTempState.cc

ZeroTempSpectrum.o: ZeroTempSpectrum.cc ZeroTempSpectrum.hh ZeroTempState.hh
	g++ -c ZeroTempSpectrum.cc

PairTempSpectrum.o: PairTempSpectrum.cc PairTempSpectrum.hh PairTempState.hh
	g++ -c PairTempSpectrum.cc

CritTempSpectrum.o: CritTempSpectrum.cc CritTempSpectrum.hh CritTempState.hh
	g++ -c CritTempSpectrum.cc

RootFinder.o: RootFinder.cc RootFinder.hh
	g++ -c RootFinder.cc $(FLAGS)

Controller.o: Controller.cc Controller.hh
	g++ -c Controller.cc

Utility.o: Utility.cc Utility.hh
	g++ -c Utility.cc

Integrator.o: Integrator.cc Integrator.hh
	g++ -c Integrator.cc

ConfigData.hh: Logger.hh Utility.hh

BaseEnvironment.hh: ConfigData.hh Logger.hh

ZeroTempEnvironment.hh: BaseEnvironment.hh

PairTempEnvironment.hh: BaseEnvironment.hh

CritTempEnvironment.hh: BaseEnvironment.hh

BaseState.hh: BaseEnvironment.hh

ZeroTempState.hh: BaseState.hh ZeroTempEnvironment.hh ZeroTempSpectrum.hh

PairTempState.hh: BaseState.hh PairTempEnvironment.hh PairTempSpectrum.hh

CritTempState.hh: BaseState.hh CritTempEnvironment.hh CritTempSpectrum.hh

Controller.hh: BaseState.hh ZeroTempState.hh PairTempState.hh CritTempState.hh
