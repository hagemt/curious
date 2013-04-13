TAG=CS2HW8

CXXFLAGS=-Wall -Wextra -pedantic -std=c++0x

CXX=$(shell which g++)
DIFF=$(shell which diff)
RM=$(shell which rm) -fv
SAY=$(shell which echo) -e "$(TAG)"

all: hw8

clean:
	$(RM) *.o
	$(RM) hw8

compare:
	$(DIFF) main.cpp cutler.cpp

test: all

.PHONY: all clean compare test

hw8: main.o
	$(CXX) $(CXXFLAGS) $< -o $@

%.o: %.cpp bidirectional_map.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
