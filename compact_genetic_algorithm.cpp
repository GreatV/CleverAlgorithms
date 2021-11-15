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


void random_bit_string(std::string& bit_string, const size_t size)
{
	bit_string.clear();
	for (size_t i = 0; i < size; ++i)
	{
		bit_string.push_back(random_() < 0.5 ? '1' : '0');
	}
}


void generate_candidate(candidate_solution& candidate, const std::vector<double>& vector)
{
	candidate.bit_string.resize(vector.size());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		const auto& p = vector[i];
		candidate.bit_string[i] = random_() < p ? '1' : '0';
	}
	candidate.fitness = onemax(candidate.bit_string);
}


void update_vector(std::vector<double>& vector,
                   const candidate_solution& winner,
                   const candidate_solution& loser,
                   const size_t pop_size)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		if (winner.bit_string[i] != loser.bit_string[i])
		{
			if (winner.bit_string[i] == '1')
			{
				vector[i] += 1.0 / pop_size;
			}
			else
			{
				vector[i] -= 1.0 / pop_size;
			}
		}
	}
}


void search(candidate_solution& best,
            const size_t num_bits,
            const size_t max_iterations,
            const size_t pop_size)
{
	std::vector<double> vector(num_bits);
	for (auto& v : vector)
	{
		v = 0.5;
	}
	for (size_t iter = 0; iter < max_iterations; ++iter)
	{
		candidate_solution c1, c2;
		generate_candidate(c1, vector);
		generate_candidate(c2, vector);

		candidate_solution winner = c1.fitness > c2.fitness ? c1 : c2;
		candidate_solution loser = c1.fitness > c2.fitness ? c2 : c1;

		if (iter == 0)
		{
			best = winner;
		}

		if (winner.fitness > best.fitness)
		{
			best = winner;
		}

		update_vector(vector, winner, loser, pop_size);

		std::cout << " > gen " << iter + 1 << ", f = "
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
	const size_t num_bits = 32;
	// algorithm configuration
	const size_t max_iter = 200;
	const size_t pop_size = 20;
	// execute the algorithm
	candidate_solution best;
	search(best, num_bits, max_iter, pop_size);

	std::cout << "Done! Solution: f = " << best.fitness;
	std::cout << ", b = " << best.bit_string << std::endl;

	return 0;
}
