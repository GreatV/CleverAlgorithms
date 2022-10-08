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


void binary_tournament(candidate_solution& candidate,
	const std::vector<candidate_solution>& pop)
{
	const auto i = static_cast<size_t>((pop.size() - 1) * random_());
	auto j = static_cast<size_t>((pop.size() - 1) * random_());
	while (j == i)
	{
		j = static_cast<size_t>((pop.size() - 1) * random_());
	}
	candidate = pop[i].fitness > pop[j].fitness ? pop[i] : pop[j];
}


void calculate_bit_probabilities(std::vector<double> & vector,
	const std::vector<candidate_solution> & pop)
{
	vector.clear();
	vector.resize(pop[0].bit_string.size());
	for(auto & item : vector)
	{
		item = 0.0;
	}
	for(auto & member : pop)
	{
		for(size_t i = 0; i < member.bit_string.size(); ++i)
		{
			vector[i] += (member.bit_string[i] - '0');
		}
	}
	for(size_t i = 0; i < vector.size(); ++i)
	{
		vector[i] = vector[i] / pop.size();
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
}


bool cmp_fitness(const candidate_solution& x, const candidate_solution& y)
{
	if (x.fitness > y.fitness)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best,
            const size_t num_bits,
            const size_t max_iter,
            const size_t pop_size,
            const size_t select_size)
{
	std::vector<candidate_solution> pop(pop_size);

	for(auto & item : pop)
	{
		random_bit_string(item.bit_string, num_bits);
		item.fitness = onemax(item.bit_string);
	}
	std::sort(pop.begin(), pop.end(), cmp_fitness);
	best = pop[0];

	for (size_t i = 0; i < max_iter; ++i)
	{
		std::vector<candidate_solution> selected(select_size);
		for(auto & item : selected)
		{
			binary_tournament(item, pop);
		}
		std::vector<double> vector;
		calculate_bit_probabilities(vector, selected);
		std::vector<candidate_solution> samples(pop_size);
		for(auto & item : samples)
		{
			generate_candidate(item, vector);
			item.fitness = onemax(item.bit_string);
		}
		std::sort(samples.begin(), samples.end(), cmp_fitness);
		if(samples[0].fitness > best.fitness)
		{
			best = samples[0];
		}
		pop = samples;

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
	const size_t pop_size = 50;
	const size_t select_size = 30;
	// execute the algorithm
	candidate_solution best;
	search(best, num_bits, max_iter, pop_size, select_size);

	std::cout << "Done! Solution: f = " << best.fitness;
	std::cout << ", b = " << best.bit_string << std::endl;

	return 0;
}
