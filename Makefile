CPPC=g++
CPPFLAGS=-Wall -std=c++11

ODIR=obj
SDIR=src
DEPS=$(SDIR)/headers
EXE=ConnectFour

App: $(ODIR)/main.o $(ODIR)/ConnectFour.o $(ODIR)/State.o $(ODIR)/Column.o $(ODIR)/AI.o
	$(CPPC) $(CPPFLAGS) -o $(EXE) $(ODIR)/main.o $(ODIR)/ConnectFour.o $(ODIR)/State.o $(ODIR)/Column.o $(ODIR)/AI.o

$(ODIR)/main.o: $(SDIR)/main.cpp $(SDIR)/ConnectFour.cpp $(SDIR)/State.cpp $(SDIR)/Column.cpp $(SDIR)/AI.cpp $(DEPS)/ConnectFour.h $(DEPS)/State.h $(DEPS)/Column.h $(DEPS)/AI.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/main.o -c $(SDIR)/main.cpp

$(ODIR)/ConnectFour.o: $(SDIR)/ConnectFour.cpp $(SDIR)/State.cpp $(SDIR)/Column.cpp $(SDIR)/AI.cpp $(DEPS)/ConnectFour.h $(DEPS)/State.h $(DEPS)/Column.h $(DEPS)/AI.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/ConnectFour.o -c $(SDIR)/ConnectFour.cpp

$(ODIR)/State.o: $(SDIR)/State.cpp $(SDIR)/Column.cpp $(DEPS)/State.h $(DEPS)/Column.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/State.o -c $(SDIR)/State.cpp

$(ODIR)/Column.o: $(SDIR)/Column.cpp $(DEPS)/Column.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/Column.o -c $(SDIR)/Column.cpp

$(ODIR)/AI.o: $(SDIR)/AI.cpp $(DEPS)/AI.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/AI.o -c $(SDIR)/AI.cpp

clean:
	rm -f ConnectFour $(SDIR)/*~ $(ODIR)/*.o $(SDIR)/*\#
