CPP = g++
CFLAGS = --std=c++11 -O2 -Wall
LIBFLAGS = -lm -lvtkCommonCore-7.0 -lvtkFiltersCore-7.0 -lvtkIOCore-7.0 -lvtkIOXML-7.0 -lvtkCommonDataModel-7.0 -L/usr/lib/x86_64-linux-gnu
INCLUDEFLAGS = -I. -I/usr/local/include/vtk-7.0

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
