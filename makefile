IDIR=include
ODIR=obj
LDIR=lib
BDIR=bin
SDIR=src
TDIR=test

CPP=g++
CPPFLAGS=-I$(IDIR) -std=c++11 -g

LIBS=-lm

_DEPS=zca.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=zca.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_BIN=main
BIN=$(patsubst %,$(BDIR)/%,$(_BIN))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

$(BIN): $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(BDIR)/* *~ core $(INCDIR)/*~