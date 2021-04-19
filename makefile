IDIR=include
ODIR=obj
LDIR=lib
BDIR=bin
SDIR=src
TDIR=test

CPP=g++
CPPFLAGS=-I$(IDIR) -std=c++11 -g

LIBS=-lm

_DEPS=zcamgr.h zserver.h zclient.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=zcamgr.o zserver.o zclient.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_BIN=main
BIN=$(patsubst %,$(BDIR)/%,$(_BIN))

_SERVER=server
SERVER=$(patsubst %,$(BDIR)/%,$(_SERVER))

_CLIENT=client
CLIENT=$(patsubst %,$(BDIR)/%,$(_CLIENT))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

$(BIN): $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS) $(LIBS)

server: $(OBJ)
	$(CPP) -o bin/server src/server.cpp obj/zserver.o $(CPPFLAGS) $(LIBS)

client: $(OBJ)
	$(CPP) -o bin/client src/client.cpp obj/zclient.o $(CPPFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(BDIR)/* *~ core $(INCDIR)/*~