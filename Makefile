TAG=CS2HW8

CXXFLAGS=-Wall -Wextra -pedantic -std=c++0x

CXX=$(shell which g++)
DIFF=$(shell which diff) -s
RM=$(shell which rm) -fv
SAY=$(shell which echo) -e "[$(TAG)]"

all: hw8 iterator.o

clean:
	@$(SAY) "Cleaning object files and executables..."
	@$(RM) *.o
	@$(RM) hw8

changes:
	@$(SAY) "Comparing current main.cpp with provided..."
	@$(DIFF) main.cpp cutler.cpp || true

test: all

.PHONY: all changes clean test

hw8: main.o node.o
	@$(SAY) "LD   $(TAG)"
	@$(CXX) $(CXXFLAGS) main.o node.o -o $@

%.o: %.cpp
	@$(SAY) "CC   $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
