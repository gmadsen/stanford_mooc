# Makefile for EECS 280 Project 4

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++17 -g
CXXFLAGSOPT = --std=c++17 -O3 


all: test

test: mult_algorithm_test.exe main.exe
	./mult_algorithm_test.exe
	./main.exe


mult_algorithm_test.exe: mult_algorithm_test.cpp mult_algorithm.cpp unit_test_framework.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@

graph_test.exe: graph_test.cpp graph.cpp unit_test_framework.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@


main.exe: main.cpp mult_algorithm.cpp graph.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@

main_optimized.exe: main.cpp graph.cpp 
	$(CXX) $(CXXFLAGSOPT) $^ -o $@




# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean:
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out

# Run style check tools
CPPCHECK ?= cppcheck
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-0.13/bin/oclint
FILES := List.h List_tests.cpp Stack.h calc.cpp
style :
	$(CPPCHECK) \
    --language=c++ \
    --std=c++11 \
    --error-exitcode=1 \
    $(FILES)
	$(OCLINT) \
    -rule=LongLine \
    -rule=HighNcssMethod \
    -rule=DeepNestedBlock \
    -rule=TooManyParameters \
    -rc=LONG_LINE=90 \
    -rc=NCSS_METHOD=40 \
    -rc=NESTED_BLOCK_DEPTH=4 \
    -rc=TOO_MANY_PARAMETERS=4 \
    -max-priority-1 0 \
    -max-priority-2 0 \
    -max-priority-3 0 \
    $(FILES) \
    -- -xc++ --std=c++11
	$(CPD) \
    --minimum-tokens 100 \
    --language cpp \
    --failOnViolation true \
    --files $(FILES)
	@echo "########################################"
	@echo "EECS 280 style checks PASS"
