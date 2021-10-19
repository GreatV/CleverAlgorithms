#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <functional>
#include <map>
#include <iostream>


typedef struct candidate_solution_st
{
	std::vector<double> vector;
	double cost;
}candidate_solution;


double objective_function(std::vector<double>& vector)
{
	return std::inner_product(vector.begin(), vector.end(), vector.begin(), 0.0);
}


void random_vector(std::vector<double>& rand_vec, std::vector<std::vector<double> >& minmax)
{
	if (minmax.empty())
	{
		return;
	}
	rand_vec.resize(minmax.size());
	std::random_device rd;
	std::mt19937 generator(rd());;
	std::uniform_real_distribution<> distribution(0.0, 1.0);
	auto random = std::bind(distribution, generator);

	for (size_t i = 0; i < minmax.size(); ++i)
	{
		rand_vec[i] = minmax[i][0] + (minmax[i][1] - minmax[i][0]) * random();
	}
}


void search(candidate_solution & best, std::vector<std::vector<double> > &search_space, size_t max_iter)
{
	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		candidate_solution candidate;
		random_vector(candidate.vector, search_space);
		candidate.cost = objective_function(candidate.vector);

		if (iter == 0)
		{
			best.vector = candidate.vector;
			best.cost = candidate.cost;
		}
		else
		{
			if (candidate.cost < best.cost)
			{
				best.vector = candidate.vector;
				best.cost = candidate.cost;
			}
		}

		std::cout << " > iteration=" << iter + 1 << ", best=" << best.cost << std::endl;
	}
}


int main(int argc, char *argv[])
{
	// problem configuration
	size_t problem_size = 2;
	std::vector<std::vector<double> > search_space;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> bound = { -5.0, 5.0 };
		search_space.push_back(bound);
	}
	// algorithm configuration
	size_t max_iter = 100;
	// execute the algorithm
	candidate_solution best;
	search(best, search_space, max_iter);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (size_t i = 0; i < best.vector.size(); ++i)
	{
		std::cout << best.vector[i] << " ";
	}
	std::cout << "}" << std::endl;

	return 0;
}
