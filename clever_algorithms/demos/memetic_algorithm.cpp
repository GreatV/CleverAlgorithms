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
	std::string bit_string;
	double fitness = DBL_MAX;
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


void random_bit_string(std::string& bit_string, const size_t num_bits)
{
	bit_string.clear();
	for (size_t i = 0; i < num_bits; ++i)
	{
		bit_string.push_back(random_() < 0.5 ? '1' : '0');
	}
}


void decode(std::vector<double>& vector,
            const std::string& bit_string,
            const std::vector<std::vector<double>>& search_space,
            const size_t bits_per_param)
{
	vector.clear();
	for (size_t i = 0; i < search_space.size(); ++i)
	{
		auto& bounds = search_space[i];
		const auto off = i * bits_per_param;
		auto sum = 0.0;
		std::string param;
		for (size_t j = off + bits_per_param; j > off; --j)
		{
			param.push_back(bit_string[j]);
		}
		for (size_t k = 0; k < param.size(); ++k)
		{
			sum += (param[k] == '1' ? 1.0 : 0.0) * pow(2.0, k);
		}
		const auto min = bounds[0];
		const auto max = bounds[1];
		vector.push_back(min + ((max - min) / (pow(2.0, bits_per_param) - 1.0)) * sum);
	}
}


void fitness(candidate_solution& candidate,
             const std::vector<std::vector<double>>& search_space,
             const size_t param_bits)
{
	decode(candidate.vector, candidate.bit_string, search_space, param_bits);
	candidate.fitness = objective_function(candidate.vector);
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
	candidate = pop[i].fitness < pop[j].fitness ? pop[i] : pop[j];
}


void point_mutation(std::string& child, const std::string& bit_string, const double rate)
{
	std::string tmp;

	for (const auto& item : bit_string)
	{
		tmp.push_back(random_() < rate ? (item == '1' ? '0' : '1') : item);
	}

	child = tmp;
}


void crossover(std::string& child,
               const std::string& parent1,
               const std::string& parent2, const double rate)
{
	if (random_() >= rate)
	{
		child = parent1;
		return;
	}
	child.clear();
	for (size_t i = 0; i < parent1.size(); ++i)
	{
		child.push_back(random_() < 0.5 ? parent1[i] : parent2[i]);
	}
}


void reproduce(std::vector<candidate_solution>& children,
               const std::vector<candidate_solution>& selected,
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


void bit_climber(candidate_solution& current,
                 const candidate_solution& child,
                 const std::vector<std::vector<double>>& search_space,
                 const double p_mut,
                 const size_t max_local_gens,
                 const size_t bits_per_param)
{
	current = child;
	for (size_t i = 0; i < max_local_gens; ++i)
	{
		candidate_solution candidate;
		point_mutation(candidate.bit_string, current.bit_string, p_mut);
		fitness(candidate, search_space, bits_per_param);
		if (candidate.fitness <= current.fitness)
		{
			current = candidate;
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
            const size_t max_gens,
            const std::vector<std::vector<double>>& search_space,
            const size_t pop_size,
            const double p_cross, const double p_mut,
            const size_t max_local_gens, const double p_local,
            const size_t bits_per_param = 16)
{
	std::vector<candidate_solution> pop(pop_size);
	for (auto& c : pop)
	{
		random_bit_string(c.bit_string, search_space.size() * bits_per_param);
		fitness(c, search_space, bits_per_param);
	}
	std::sort(pop.begin(), pop.end(), cmp_fitness);
	best = pop[0];

	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		std::vector<candidate_solution> selected(pop_size);
		for (auto& c : selected)
		{
			binary_tournament(c, pop);
		}
		std::vector<candidate_solution> children;
		reproduce(children, selected, pop_size, p_cross, p_mut);
		for (auto& c : children)
		{
			fitness(c, search_space, bits_per_param);
		}
		pop.clear();
		for (auto& child : children)
		{
			if (random_() < p_local)
			{
				candidate_solution tmp_child;
				bit_climber(tmp_child, child, search_space, p_mut, max_local_gens, bits_per_param);
				child = tmp_child;
			}
			pop.push_back(child);
		}
		std::sort(pop.begin(), pop.end(), cmp_fitness);
		if (pop[0].fitness <= best.fitness)
		{
			best = pop[0];
		}

		std::cout << " > gen " << gen + 1 << ", f = "
			<< best.fitness << ", b = "
			<< best.bit_string << std::endl;
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
	const size_t max_gens = 100;
	const size_t pop_size = 100;
	const double p_cross = 0.98;
	const double p_mut = 1.0 / (problem_size * 16.0);
	const size_t max_local_gens = 20;
	const double p_local = 0.5;
	// execute the algorithm
	candidate_solution best;
	search(best, max_gens, bounds, pop_size, p_cross,
	       p_mut, max_local_gens, p_local);

	std::cout << "Done! Solution: f = " << best.fitness << ", v = { ";
	for (const auto& i : best.vector)
		std::cout << i << " ";
	std::cout << "}";
	std::cout << ", b = " << best.bit_string << std::endl;

	return 0;
}
