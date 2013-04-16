TAG=CS2HW8

CXXFLAGS=-Wall -Wextra -ggdb -pedantic -std=c++0x

CXX=$(shell which g++)
DIFF=$(shell which diff) -s
RM=$(shell which rm) -fv
SAY=$(shell which echo) -e "[$(TAG)]"

all: iterator.o map.o hw8

clean:
	@$(SAY) "Cleaning generated, object, and executable files..."
	@$(RM) *.pch *.gch
	@$(RM) *.o hw8

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
