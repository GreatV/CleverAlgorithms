#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::vector<double> vector;
	std::vector<double> strategy;
	double fitness = 0;
	size_t wins = 0;
};


double objective_function(const std::vector<double>& vector)
{
	double sum = 0.0;
	for (const double val : vector)
	{
		sum += val * val;
	}

	return sum;
}


void random_vector(std::vector<double>& arr, const std::vector<std::vector<double>>& minmax)
{
	arr.clear();
	for (const auto& item : minmax)
	{
		arr.push_back(item[0] + (item[1] - item[0]) * random_());
	}
}


double random_gaussian(const double mean = 0.0, const double stdev = 1.0)
{
	double u1 = 0.0, u2 = 0.0, w = 0.0;
	u1 = 2 * random_() - 1;
	u2 = 2 * random_() - 1;
	w = u1 * u1 + u2 * u2;
	while (w >= 1)
	{
		u1 = 2 * random_() - 1;
		u2 = 2 * random_() - 1;
		w = u1 * u1 + u2 * u2;
	}
	w = sqrt((-2.0 * log(w)) / w);
	return mean + (u2 * w) * stdev;
}


void mutate(candidate_solution& child, const candidate_solution& candidate,
            const std::vector<std::vector<double>>& search_space)
{
	child.vector.clear();
	child.strategy.clear();
	for (size_t i = 0; i < candidate.vector.size(); ++i)
	{
		const auto v_old = candidate.vector[i];
		const auto s_old = candidate.strategy[i];

		auto v = v_old + s_old * random_gaussian();
		if (v < search_space[i][0])
			v = search_space[i][0];
		if (v > search_space[i][1])
			v = search_space[i][1];

		child.vector.push_back(v);
		child.strategy.push_back(s_old + random_gaussian() * sqrt(abs(s_old)));
	}
}


void tournament(candidate_solution& candidate, const std::vector<candidate_solution>& population,
                const size_t bout_size)
{
	candidate.wins = 0;
	for (size_t i = 0; i < bout_size; ++i)
	{
		auto& other = population[static_cast<size_t>((population.size() - 1) * random_())];
		if (candidate.fitness < other.fitness)
		{
			candidate.wins += 1;
		}
	}
}


void init_population(std::vector<candidate_solution>& pop,
                     const std::vector<std::vector<double>>& minmax,
                     const size_t pop_size)
{
	std::vector<std::vector<double>> strategy;
	for (const auto& bound : minmax)
	{
		std::vector<double> tmp_bound;
		tmp_bound.push_back(0);
		tmp_bound.push_back((bound[1] - bound[0]) * 0.05);
		strategy.push_back(tmp_bound);
	}
	pop.clear();
	pop.resize(pop_size);
	for (auto& p : pop)
	{
		random_vector(p.vector, minmax);
		random_vector(p.strategy, strategy);
		p.fitness = objective_function(p.vector);
	}
}


bool cmp_fitness(const candidate_solution& c_l, const candidate_solution& c_r)
{
	if (c_l.fitness < c_r.fitness)
	{
		return true;
	}

	return false;
}


bool cmp_wins(const candidate_solution& c_l, const candidate_solution& c_r)
{
	if (c_l.wins > c_r.wins)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best, const size_t max_gens,
            const std::vector<std::vector<double>>& search_space,
            const size_t pop_size, const size_t bout_size)
{
	std::vector<candidate_solution> population;
	init_population(population, search_space, pop_size);
	std::sort(population.begin(), population.end(), cmp_fitness);
	best = population[0];
	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		std::vector<candidate_solution> children(pop_size);
		for (size_t i = 0; i < children.size(); ++i)
		{
			mutate(children[i], population[i], search_space);
			children[i].fitness = objective_function(children[i].vector);
		}
		std::sort(children.begin(), children.end(), cmp_fitness);
		if (children[0].fitness < best.fitness)
			best = children[0];
		std::vector<candidate_solution> union_set(children.size() + population.size());
		for (size_t i = 0; i < children.size(); ++i)
		{
			union_set[i] = children[i];
		}

		for (size_t i = 0; i < population.size(); ++i)
		{
			union_set[i + children.size()] = population[i];
		}

		for (size_t i = 0; i < union_set.size(); ++i)
		{
			tournament(union_set[i], union_set, bout_size);
		}

		std::sort(union_set.begin(), union_set.end(), cmp_wins);
		for (size_t i = 0; i < pop_size; ++i)
		{
			population[i] = union_set[i];
		}

		std::cout << " > gen " << gen << ", best: " << best.fitness << std::endl;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 3;
	std::vector<std::vector<double>> search_space;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> space{-5, 5};
		search_space.push_back(space);
	}
	// algorithm configuration
	const size_t max_gens = 200;
	const size_t pop_size = 100;
	const size_t bout_size = 5;
	// execute the algorithm
	candidate_solution best;
	search(best, max_gens, search_space, pop_size, bout_size);

	std::cout << "Done. Solution: f = " << best.fitness << ", s = ";
	for (auto& vec : best.vector)
		std::cout << vec << " ";
	std::cout << std::endl;

	return 0;
}
