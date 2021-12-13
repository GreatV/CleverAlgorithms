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
	std::string bit_string;
	double fitness = DBL_MIN;
};


double onemax(const std::string& bit_string)
{
	double sum = 0.0;
	for (auto& item : bit_string)
	{
		if (item == '1')
		{
			sum++;
		}
	}
	return sum;
}


void generate_candidate(candidate_solution& candidate, const std::vector<double>& vector)
{
	candidate.bit_string.resize(vector.size());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		const auto& p = vector[i];
		candidate.bit_string[i] = random_() < p ? '1' : '0';
	}
}


void update_vector(std::vector<double>& vector, const candidate_solution& current, const double l_rate)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		const auto& p = vector[i];
		vector[i] = p * (1.0 - l_rate) + current.bit_string[i] * l_rate;
	}
}


void mutate_vector(std::vector<double>& vector,
                   const candidate_solution& current,
                   const double coefficient,
                   const double rate)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		const auto& p = vector[i];
		if (random_() < rate)
		{
			vector[i] = p * (1.0 - coefficient) + random_() * coefficient;
		}
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
            const size_t num_bits,
            const size_t max_iter,
            const size_t num_samples,
            const double p_mutate,
            const double mut_factor,
            const double l_rate)
{
	std::vector<double> vector(num_bits);
	for (auto& item : vector)
	{
		item = 0.5;
	}
	for (size_t i = 0; i < max_iter; ++i)
	{
		candidate_solution current;
		for (size_t j = 0; j < num_samples; ++j)
		{
			candidate_solution candidate;
			generate_candidate(candidate, vector);
			candidate.fitness = onemax(candidate.bit_string);
			if (i == 0)
			{
				current = candidate;
				best = candidate;
			}

			if (candidate.fitness > current.fitness)
			{
				current = candidate;
			}

			if (candidate.fitness > best.fitness)
			{
				best = candidate;
			}
		}
		update_vector(vector, current, l_rate);
		mutate_vector(vector, current, mut_factor, p_mutate);
		std::cout << " > gen " << i + 1 << ", f = "
			<< best.fitness << ", b = "
			<< best.bit_string << std::endl;

		if (static_cast<size_t>(best.fitness) == num_bits)
		{
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t num_bits = 64;
	// algorithm configuration
	const size_t max_iter = 100;
	const size_t num_sample = 100;
	const double p_mutate = 1.0 / num_bits;
	const double mut_factor = 0.05;
	const double l_rate = 0.1;
	// execute the algorithm
	candidate_solution best;
	search(best, num_bits, max_iter, num_sample, p_mutate,
	       mut_factor, l_rate);

	std::cout << "Done! Solution: f = " << best.fitness;
	std::cout << ", b = " << best.bit_string << std::endl;

	return 0;
}
