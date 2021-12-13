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
	std::string bit_string;
	double fitness = 0.0;
};


double onemax(std::string& bit_string)
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


void random_bit_string(std::string& bit_string, const size_t num_bits)
{
	bit_string.clear();
	for (size_t i = 0; i < num_bits; ++i)
	{
		bit_string.push_back(random_() < 0.5 ? '1' : '0');
	}
}


void binary_tournament(candidate_solution& candidate, std::vector<candidate_solution>& pop)
{
	const auto i = static_cast<size_t>((pop.size() - 1) * random_());
	auto j = static_cast<size_t>((pop.size() - 1) * random_());
	while (j == i)
	{
		j = static_cast<size_t>((pop.size() - 1) * random_());
	}
	candidate = pop[i].fitness > pop[j].fitness ? pop[i] : pop[j];
}


void point_mutation(std::string& child, std::string& bit_string, const double rate)
{
	std::string tmp;

	for (auto& item : bit_string)
	{
		tmp.push_back(random_() < rate ? (item == '1' ? '0' : '1') : item);
	}

	child = tmp;
}


void crossover(std::string& child, std::string& parent1, std::string& parent2, const double rate)
{
	if (random_() >= rate)
	{
		child = parent1;
	}

	const size_t point = 1 + static_cast<size_t>((parent1.size() - 3) * random_());

	child.clear();
	for (size_t i = 0; i < point; ++i)
	{
		child.push_back(parent1[i]);
	}
	for (size_t i = point; i < parent1.size(); ++i)
	{
		child.push_back(parent2[i]);
	}
}


void reproduce(std::vector<candidate_solution>& children, std::vector<candidate_solution>& selected,
               const size_t pop_size, const double p_cross, const double p_mutation)
{
	children.clear();
	for (size_t i = 0; i < selected.size(); ++i)
	{
		auto p1 = selected[i];
		auto p2 = i % 2 == 0 ? (i == selected.size() - 1 ? selected[0] : selected[i + 1]) : selected[i - 1];
		candidate_solution child;
		crossover(child.bit_string, p1.bit_string, p2.bit_string, p_cross);
		point_mutation(child.bit_string, child.bit_string, p_mutation);
		children.push_back(child);

		if (children.size() >= pop_size)
		{
			break;
		}
	}
}


bool cmp(candidate_solution& candidate1, candidate_solution& candidate2)
{
	if (candidate1.fitness > candidate2.fitness)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best, const size_t max_gens, const size_t num_bits, const size_t pop_size,
            const double p_crossover, const double p_mutation)
{
	std::vector<candidate_solution> population;
	for (size_t i = 0; i < pop_size; ++i)
	{
		candidate_solution candidate;
		random_bit_string(candidate.bit_string, num_bits);
		candidate.fitness = onemax(candidate.bit_string);
		population.push_back(candidate);
	}

	std::sort(population.begin(), population.end(), cmp);
	best = population[0];

	for (size_t i = 0; i < max_gens; ++i)
	{
		std::vector<candidate_solution> selected;
		for (size_t j = 0; j < pop_size; ++j)
		{
			candidate_solution tmp_candidate;
			binary_tournament(tmp_candidate, population);
			selected.push_back(tmp_candidate);
		}
		std::vector<candidate_solution> children;
		reproduce(children, selected, pop_size, p_crossover, p_mutation);
		for (auto& item : children)
		{
			item.fitness = onemax(item.bit_string);
		}
		std::sort(children.begin(), children.end(), cmp);
		if (children[0].fitness >= best.fitness)
		{
			best = children[0];
		}
		population = children;
		std::cout << " > gen " << i << ", best: " << best.fitness
			<< ", " << best.bit_string << std::endl;

		if (static_cast<size_t>(best.fitness) == num_bits)
			break;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t num_bits = 64;
	// algorithm configuration
	const size_t max_gens = 100;
	const size_t pop_size = 100;
	const double p_crossover = 0.98;
	const double p_mutation = 1.0 / num_bits;
	// execute the algorithm
	candidate_solution best;
	search(best, max_gens, num_bits, pop_size, p_crossover, p_mutation);

	std::cout << "Done. Solution: f = " << best.fitness << ", s = " << best.bit_string << std::endl;

	return 0;
}
