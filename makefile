.PHONY:clean all

CXX=g++
CXXFLAGS=-Wall -std=c++14 -O2

BIN=random_search adaptive_random_search stochastic_hill_climbing \
iterated_local_search guided_local_search variable_neighborhood_search \
greedy_randomized_adaptive_search scatter_search tabu_search \
reactive_tabu_search genetic_algorithm evolution_strategies \
differential_evolution evolutionary_programming simulated_annealing \
extremal_optimization harmony_search cultural_algorithm \
memetic_algorithm population-based_incremental_learning \
univariate_marginal_distribution_algorithm \
compact_genetic_algorithm bayesian_optimization_algorithm \
cross-entropy_method

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

guided_local_search:guided_local_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

variable_neighborhood_search:variable_neighborhood_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

greedy_randomized_adaptive_search:greedy_randomized_adaptive_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

scatter_search:scatter_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tabu_search:tabu_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

reactive_tabu_search:reactive_tabu_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

genetic_algorithm:genetic_algorithm.o
	$(CXX) $(CXXFLAGS) -o $@ $^

evolution_strategies:evolution_strategies.o
	$(CXX) $(CXXFLAGS) -o $@ $^

differential_evolution:differential_evolution.o
	$(CXX) $(CXXFLAGS) -o $@ $^

evolutionary_programming:evolutionary_programming.o
	$(CXX) $(CXXFLAGS) -o $@ $^

simulated_annealing:simulated_annealing.o
	$(CXX) $(CXXFLAGS) -o $@ $^

extremal_optimization:extremal_optimization.o
	$(CXX) $(CXXFLAGS) -o $@ $^

harmony_search:harmony_search.o
	$(CXX) $(CXXFLAGS) -o $@ $^

cultural_algorithm:cultural_algorithm.o
	$(CXX) $(CXXFLAGS) -o $@ $^

memetic_algorithm:memetic_algorithm.o
	$(CXX) $(CXXFLAGS) -o $@ $^

population-based_incremental_learning:population-based_incremental_learning.o
	$(CXX) $(CXXFLAGS) -o $@ $^

univariate_marginal_distribution_algorithm:univariate_marginal_distribution_algorithm.o
	$(CXX) $(CXXFLAGS) -o $@ $^

compact_genetic_algorithm:compact_genetic_algorithm.o
	$(CXX) $(CXXFLAGS) -o $@ $^

bayesian_optimization_algorithm:bayesian_optimization_algorithm.o
	$(CXX) $(CXXFLAGS) -o $@ $^

cross-entropy_method:cross-entropy_method.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN) *.o
