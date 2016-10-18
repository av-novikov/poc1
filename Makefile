CPP = g++
CFLAGS = --std=c++11 -O2 -Wall
LIBFLAGS = -lm
INCLUDEFLAGS = -I.

SOURCEDIR = ./src

# c++ sources
CSOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
COBJECTS = $(CSOURCES:%.cpp=%.o)

EXECUTABLE = ./bin/poc1

all: $(EXECUTABLE)

$(EXECUTABLE): $(COBJECTS)
	$(CPP) $(CFLAGS) $(INCLUDEFLAGS) main.cpp $(COBJECTS) -o $@ $(LIBFLAGS)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@ $(LIBFLAGS)
	
clean:
	rm -f $(COBJECTS) $(EXECUTABLE)
