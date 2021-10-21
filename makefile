.PHONY:clean all

CXX=g++
CXXFLAGS=-Wall -std=c++14 -O2

BIN=random_search adaptive_random_search stochastic_hill_climbing \
iterated_local_search

all: $(BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

random_search:random_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

adaptive_random_search:adaptive_random_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

stochastic_hill_climbing:stochastic_hill_climbing.o
	$(CXX) $(CXXFLAGS) -o $@ $^

iterated_local_search:iterated_local_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN) *.o
