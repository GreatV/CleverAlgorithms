#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <cfloat>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_st
{
	std::vector<double> vector;
	double fitness = DBL_MAX;
};


using belief_info = struct belief_info_st
{
	std::vector<std::vector<double>> normative;
	candidate_solution situational;
};

double objective_function(const std::vector<double>& vector)
{
	double sum = 0.0;
	for (const double& i : vector)
	{
		sum += i * i;
	}

	return sum;
}


double rand_in_bounds(const double min, const double max)
{
	return min + (max - min) * random_();
}


void random_vector(std::vector<double>& vector,
                   const std::vector<std::vector<double>>& search_space)
{
	vector.clear();
	vector.resize(search_space.size());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		vector[i] = rand_in_bounds(search_space[i][0], search_space[i][1]);
	}
}


void mutate_with_inf(std::vector<double>& vector,
                     const candidate_solution& candidate,
                     const belief_info& beliefs,
                     const std::vector<std::vector<double>>& minmax)
{
	vector.clear();
	vector.resize(candidate.vector.size());
	for (size_t i = 0; i < candidate.vector.size(); ++i)
	{
		// auto& c = candidate.vector[i];
		vector[i] = rand_in_bounds(beliefs.normative[i][0], beliefs.normative[i][1]);
		if (vector[i] < minmax[i][0])
			vector[i] = minmax[i][0];
		if (vector[i] > minmax[i][1])
			vector[i] = minmax[i][1];
	}
}


void binary_tournament(candidate_solution& candidate,
                       const std::vector<candidate_solution>& pop)
{
	auto i = static_cast<size_t>((pop.size() - 1) * random_());
	auto j = static_cast<size_t>((pop.size() - 1) * random_());
	while (j == i)
	{
		j = static_cast<size_t>((pop.size() - 1) * random_());
	}
	candidate = pop[i].fitness < pop[j].fitness ? pop[i] : pop[j];
}


void initialize_beliefspace(belief_info& belief_space,
                            const std::vector<std::vector<double>>& search_space)
{
	belief_space.normative.clear();
	belief_space.normative.resize(search_space.size());
	for (size_t i = 0; i < search_space.size(); ++i)
	{
		belief_space.normative[i] = search_space[i];
	}
}


void update_beliefspace_situational(belief_info& belief_space,
                                    const candidate_solution& best)
{
	auto& curr_best = belief_space.situational;
	if (best.fitness < curr_best.fitness)
	{
		belief_space.situational = best;
	}
}


void update_beliefspace_normative(belief_info& belief_space,
                                  const std::vector<candidate_solution>& acc)
{
	for (size_t i = 0; i < belief_space.normative.size(); ++i)
	{
		auto& bounds = belief_space.normative[i];
		double max_val = DBL_MIN, min_val = DBL_MAX;
		for (const auto& item : acc)
		{
			if (max_val < item.vector[i])
			{
				max_val = item.vector[i];
			}

			if (min_val > item.vector[i])
			{
				min_val = item.vector[i];
			}
		}
		bounds[0] = min_val;
		bounds[1] = max_val;
	}
}


bool cmp_fitness(const candidate_solution& x, const candidate_solution& y)
{
	if (x.fitness < y.fitness)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best,
            const size_t max_gens,
            const std::vector<std::vector<double>>& search_space,
            const size_t pop_size,
            const size_t num_accepted)
{
	// initialize
	std::vector<candidate_solution> pop(pop_size);
	for (auto& item : pop)
	{
		random_vector(item.vector, search_space);
	}
	belief_info belief_space;
	initialize_beliefspace(belief_space, search_space);

	// evaluate
	for (auto& c : pop)
	{
		c.fitness = objective_function(c.vector);
	}
	std::sort(pop.begin(), pop.end(), cmp_fitness);
	best = pop[0];

	// update situational knowledge
	update_beliefspace_situational(belief_space, best);
	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		// create next generation
		std::vector<candidate_solution> children(pop_size);
		for (size_t i = 0; i < pop_size; ++i)
		{
			mutate_with_inf(children[i].vector, pop[i], belief_space, search_space);
		}

		// evaluate
		for (auto& child : children)
		{
			child.fitness = objective_function(child.vector);
		}
		std::sort(children.begin(), children.end(), cmp_fitness);
		best = children[0];

		// update situational knowledge
		update_beliefspace_situational(belief_space, best);

		// select next generation
		std::vector<candidate_solution> tmp_pop;
		tmp_pop.reserve(pop.size());
		for (const auto& i : pop)
		{
			tmp_pop.push_back(i);
		}
		for (const auto& i : children)
		{
			tmp_pop.push_back(i);
		}
		pop.clear();
		for (size_t i = 0; i < pop_size; ++i)
		{
			candidate_solution c;
			binary_tournament(c, tmp_pop);
			pop.push_back(c);
		}

		// update normative knowledge
		std::sort(pop.begin(), pop.end(), cmp_fitness);
		std::vector<candidate_solution> accepted(num_accepted);
		for (size_t i = 0; i < num_accepted; ++i)
		{
			accepted[i] = pop[i];
		}
		update_beliefspace_normative(belief_space, accepted);

		std::cout << " > generation " << gen + 1 << ", fitness = "
			<< belief_space.situational.fitness << std::endl;
	}

	best = belief_space.situational;
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 3;
	std::vector<std::vector<double>> bounds;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> bound{-5.0, 5.0};
		bounds.push_back(bound);
	}
	// algorithm configuration
	const size_t max_gens = 200;
	const size_t pop_size = 100;
	const size_t num_accepted = static_cast<size_t>((pop_size * 0.2) * random_());
	// execute the algorithm
	candidate_solution best;
	search(best, max_gens, bounds, pop_size, num_accepted);

	std::cout << "Done. Best Solution: c=" << best.fitness << ", v={ ";
	for (auto& i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
