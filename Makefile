CPPC=g++
CPPFLAGS=-Wall -std=c++11

ODIR=obj
SDIR=src
DEPS=$(SDIR)/headers

ConnectFour: $(ODIR)/main.o $(ODIR)/State.o $(ODIR)/Column.o
	$(CPPC) $(CPPFLAGS) -o ConnectFour $(ODIR)/main.o $(ODIR)/State.o $(ODIR)/Column.o

$(ODIR)/main.o: $(SDIR)/main.cpp $(SDIR)/State.cpp $(SDIR)/Column.cpp $(DEPS)/State.h $(DEPS)/Column.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/main.o -c $(SDIR)/main.cpp

$(ODIR)/State.o: $(SDIR)/State.cpp $(SDIR)/Column.cpp $(DEPS)/State.h $(DEPS)/Column.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/State.o -c $(SDIR)/State.cpp

$(ODIR)/Column.o: $(SDIR)/Column.cpp $(DEPS)/Column.h
	$(CPPC) $(CPPFLAGS) -o $(ODIR)/Column.o -c $(SDIR)/Column.cpp

clean:
	rm -f ConnectFour $(SDIR)/*~ $(ODIR)/*.o $(SDIR)/*\#
