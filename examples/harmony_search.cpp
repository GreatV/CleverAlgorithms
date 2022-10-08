#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_st
{
	std::vector<double> vector;
	double fitness = 0.0;
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


void create_random_harmony(candidate_solution& harmony,
                           const std::vector<std::vector<double>>& search_space)
{
	random_vector(harmony.vector, search_space);
	harmony.fitness = objective_function(harmony.vector);
}


bool cmp_fitness(const candidate_solution& x, const candidate_solution& y)
{
	if (x.fitness < y.fitness)
	{
		return true;
	}
	return false;
}


void initialize_harmony_memory(std::vector<candidate_solution>& memory,
                               const std::vector<std::vector<double>>& search_space,
                               const size_t mem_size,
                               const double factor = 3.0)
{
	memory.clear();
	memory.resize(static_cast<size_t>(mem_size * factor));
	for (auto& item : memory)
	{
		create_random_harmony(item, search_space);
	}
	std::sort(memory.begin(), memory.end(), cmp_fitness);

	memory.resize(mem_size);
}


void create_harmony(std::vector<double>& vector,
                    const std::vector<std::vector<double>>& search_space,
                    const std::vector<candidate_solution>& memory,
                    const double consid_rate,
                    const double adjust_rate,
                    const double range
)
{
	vector.clear();
	vector.resize(search_space.size());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		if (random_() < consid_rate)
		{
			auto value = memory[static_cast<size_t>(random_() * (memory.size() - 1))].vector[i];
			if (random_() < adjust_rate)
				value += range * rand_in_bounds(-1.0, 1.0);

			if (value < search_space[i][0])
				value = search_space[i][0];

			if (value > search_space[i][1])
				value = search_space[i][1];

			vector[i] = value;
		}
		else
		{
			vector[i] = rand_in_bounds(search_space[i][0], search_space[i][1]);
		}
	}
}


void search(candidate_solution& best,
            const std::vector<std::vector<double>>& bounds,
            const size_t max_iter, const size_t meme_size,
            const double consid_rate, const double adjust_rate,
            const double range)
{
	std::vector<candidate_solution> memory;
	initialize_harmony_memory(memory, bounds, meme_size);
	best = memory[0];
	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		candidate_solution harm;
		create_harmony(harm.vector, bounds, memory, consid_rate, adjust_rate, range);
		harm.fitness = objective_function(harm.vector);
		if (harm.fitness < best.fitness)
		{
			best = harm;
		}
		memory.push_back(harm);
		std::sort(memory.begin(), memory.end(), cmp_fitness);
		memory.pop_back();
		std::cout << " > iteration " << iter + 1 << ", fitness = "
			<< best.fitness << std::endl;
	}
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
	const size_t mem_size = 20;
	const double consid_rate = 0.95;
	const double adjust_rate = 0.7;
	const double range = 0.05;
	const size_t max_iter = 500;
	// execute the algorithm
	candidate_solution best;
	search(best, bounds, max_iter, mem_size, consid_rate, adjust_rate, range);

	std::cout << "Done. Best Solution: c=" << best.fitness << ", v={ ";
	for (auto& i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
