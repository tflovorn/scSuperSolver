all: mainController.out

tests: test_Logger.out test_ConfigData.out test_Environment.out test_State.out \
test_BZone.out test_RootFinder.out test_Controller.out test_Utility.out

clean:
	\rm -f *.gch *.o *.out *.pyc *.pyo test_out.fd test_err test_Logger_log test_debug test_cfg_rewrite test_FileDict_rewrite.fd test_out2.fd test_out3.fd test_out4.fd test_err2 test_err3 test_err4 test_debug2 test_debug3 test_debug4 test_xrun*

OBJS = Logger.o ConfigData.o Environment.o State.o BZone.o Spectrum.o \
RootFinder.o Controller.o Utility.o

FLAGS = -Wall -lgsl -lblas -I/usr/local/include/gsl/

mainController.out: mainController.o $(OBJS)
	g++ -o mainController.out mainController.o $(FLAGS) $(OBJS)

test_Logger.out: test_Logger.o $(OBJS)
	g++ -o test_Logger.out test_Logger.o $(FLAGS) $(OBJS)

test_ConfigData.out: test_ConfigData.o $(OBJS)
	g++ -o test_ConfigData.out test_ConfigData.o $(FLAGS) $(OBJS)

test_Environment.out: test_Environment.o $(OBJS)
	g++ -o test_Environment.out test_Environment.o $(FLAGS) $(OBJS)

test_State.out: test_State.o $(OBJS)
	g++ -o test_State.out test_State.o $(FLAGS) $(OBJS)

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

test_Environment.o: test_Environment.cc Environment.hh
	g++ -c test_Environment.cc

test_State.o: test_State.cc State.hh
	g++ -c test_State.cc

test_BZone.o: test_BZone.cc BZone.hh State.hh
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

Environment.o: Environment.cc Environment.hh
	g++ -c Environment.cc

State.o: State.cc State.hh RootFinder.hh
	g++ -c State.cc

BZone.o: BZone.cc BZone.hh State.hh
	g++ -c BZone.cc

Spectrum.o: Spectrum.cc Spectrum.hh State.hh
	g++ -c Spectrum.cc

RootFinder.o: RootFinder.cc RootFinder.hh
	g++ -c RootFinder.cc $(FLAGS)

Controller.o: Controller.cc Controller.hh
	g++ -c Controller.cc

Utility.o: Utility.cc Utility.hh
	g++ -c Utility.cc

Environment.hh: ConfigData.hh Logger.hh

State.hh: Environment.hh

Controller.hh: State.hh
