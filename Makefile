H_FOLD='header'
CXX=g++
CC=g++
CXXFLAGS=-I$(H_FOLD) -Wall -std=c++11 -ggdb
CCFLAGS=-Wall

OBJECTS=main.o TFE.o ABNode.o ABT.o grid_util.o config.o

main: $(OBJECTS)

clean:
	rm -f main $(OBJECTS)