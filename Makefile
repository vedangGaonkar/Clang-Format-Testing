# Provided by Paul Hinker

# SRC is set to all the .cpp files in the current directory.  This can cause
# trouble if there are source files in the local directory which are not to be
# used in building the main target

SRC = $(wildcard *.cpp)

# The OBJ macro is built from the SRC macro

OBJ = $(SRC:.cpp=.o)

# Macros for the compiler, linker, and compiler options

GCC = g++
LINK = g++

CFLAGS = -Wall -g -std=c++11
CXXFLAGS = $(CFLAGS)

all: main
 
# The 'main' target depends on the files in the OBJ macro
# $^ is a make macro that contains the target dependencies
# $@ is a make macro that contains the target

main: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

# Add a clean target to allow rebuilds

clean:
	rm -rf main *.o
