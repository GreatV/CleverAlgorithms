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


void mutate_problem(std::vector<double>& child, const std::vector<double>& vector,
                    const std::vector<double>& stdevs, const std::vector<std::vector<double>>& search_space)
{
	child.clear();
	child.resize(vector.size());

	for (size_t i = 0; i < child.size(); ++i)
	{
		const double v = vector[i];
		child[i] = v + stdevs[i] * random_gaussian();
		if (child[i] < search_space[i][0])
			child[i] = search_space[i][0];
		if (child[i] > search_space[i][1])
			child[i] = search_space[i][1];
	}
}


void mutate_strategy(std::vector<double>& child, const std::vector<double>& stdevs)
{
	const double stdevs_size = stdevs.size();
	const double tau = 1 / sqrt(2.0 * stdevs_size);
	const double tau_p = 1 / sqrt(2.0 * sqrt(stdevs_size));

	child.clear();
	child.resize(stdevs.size());
	for (size_t i = 0; i < child.size(); ++i)
	{
		child[i] = stdevs[i] * exp(tau_p * random_gaussian() + tau * random_gaussian());
	}
}


void mutate(candidate_solution& child, const candidate_solution& par,
            const std::vector<std::vector<double>>& minmax)
{
	mutate_problem(child.vector, par.vector, par.strategy, minmax);
	mutate_strategy(child.strategy, par.strategy);
}


void init_population(std::vector<candidate_solution>& pop,
                     const std::vector<std::vector<double>>& minmax, const size_t pop_size)
{
	std::vector<std::vector<double>> strategy;
	for (const auto& item : minmax)
	{
		std::vector<double> tmp;
		tmp.push_back(0);
		tmp.push_back((item[1] - item[0]) * 0.05);
		strategy.push_back(tmp);
	}

	pop.clear();
	pop.resize(pop_size);
	for (auto& item : pop)
	{
		random_vector(item.vector, minmax);
		random_vector(item.strategy, strategy);
		item.fitness = objective_function(item.vector);
	}
}


bool cmp(const candidate_solution& c_l, const candidate_solution& c_r)
{
	if (c_l.fitness < c_r.fitness)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best, const size_t max_gens,
            const std::vector<std::vector<double>>& search_space, const size_t pop_size, const size_t num_children)
{
	std::vector<candidate_solution> population;
	init_population(population, search_space, pop_size);
	std::sort(population.begin(), population.end(), cmp);
	best = population[0];
	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		std::vector<candidate_solution> children(num_children);
		for (size_t i = 0; i < num_children; ++i)
		{
			mutate(children[i], population[i], search_space);
			children[i].fitness = objective_function(children[i].vector);
		}
		std::vector<candidate_solution> union_set(population.size() + children.size());
		for (size_t i = 0; i < population.size(); ++i)
		{
			union_set[i] = population[i];
		}
		for (size_t i = 0; i < children.size(); ++i)
		{
			union_set[i + pop_size] = children[i];
		}
		std::sort(union_set.begin(), union_set.end(), cmp);
		if (union_set[0].fitness < best.fitness)
		{
			best = union_set[0];
		}
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
	const size_t problem_size = 2;
	std::vector<std::vector<double>> search_space;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> space{-5, 5};
		search_space.push_back(space);
	}
	// algorithm configuration
	const size_t max_gens = 100;
	const size_t pop_size = 30;
	const size_t num_children = 20;
	// execute the algorithm
	candidate_solution best;
	search(best, max_gens, search_space, pop_size, num_children);

	std::cout << "Done. Solution: f = " << best.fitness << ", s = ";
	for (auto& vec : best.vector)
		std::cout << vec << " ";
	std::cout << std::endl;

	return 0;
}
