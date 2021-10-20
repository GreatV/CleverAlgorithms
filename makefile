.PHONY:clean all

CC=g++
CFLAGS=-Wall -std=c++14 -O2

BIN=random_search adaptive_random_search stochastic_hill_climbing \
iterated_local_search

all: $(BIN)

#%.o:%.cpp
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

random_search:random_search.o
	$(CC) $(CFLAGS) -o $@ $^

adaptive_random_search:adaptive_random_search.o
	$(CC) $(CFLAGS) -o $@ $^

stochastic_hill_climbing:stochastic_hill_climbing.o
	$(CC) $(CFLAGS) -o $@ $^

iterated_local_search:iterated_local_search.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BIN) *.o
