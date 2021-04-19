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


test_server: $(OBJ)
	$(CPP) -o bin/test_server src/test_server.cpp obj/zserver.o obj/zcamgr.o $(CPPFLAGS) $(LIBS)

test_client: $(OBJ)
	$(CPP) -o bin/test_client src/test_client.cpp obj/zclient.o obj/zcamgr.o $(CPPFLAGS) $(LIBS)

test: test_server test_client


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(BDIR)/* *~ core $(INCDIR)/*~