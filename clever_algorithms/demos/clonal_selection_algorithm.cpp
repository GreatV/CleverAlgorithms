#include <vector>
#include <random>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

using candidate_solution = struct candidate_solution_st
{
	std::vector<double> vector;
	std::string bit_string;
	double fitness = DBL_MAX;
	double affinity = 0.0;
};

double objective_function(const std::vector<double>& x)
{
	double sum = 0.0;
	for (auto& xi : x)
	{
		sum += xi * xi;
	}
	return sum;
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

void evaluate(std::vector<candidate_solution>& population,
              const std::vector<std::vector<double>>& search_space,
              const size_t bits_per_param)
{
	for (auto& candidate : population)
	{
		decode(candidate.vector, candidate.bit_string, search_space, bits_per_param);
		candidate.fitness = objective_function(candidate.vector);
	}
}

void random_bit_string(std::string& bit_string, const size_t num_bits)
{
	bit_string.clear();
	for (size_t i = 0; i < num_bits; ++i)
	{
		bit_string.push_back(random_double() < 0.5 ? '1' : '0');
	}
}

void point_mutation(std::string& child,
                    const std::string& bit_string,
                    const double rate)
{
	std::string tmp;

	for (const auto& item : bit_string)
	{
		tmp.push_back(random_double() < rate ? (item == '1' ? '0' : '1') : item);
	}
	child = tmp;
}

double calculate_mutation_rate(const candidate_solution& anti_body,
                               const double mutate_factor = -2.5)
{
	return exp(mutate_factor * anti_body.affinity);
}

size_t num_clones(const size_t pop_size, const double clone_factor)
{
	return static_cast<size_t>(pop_size * clone_factor);
}

void calculate_affinity(std::vector<candidate_solution>& pop)
{
	std::sort(pop.begin(), pop.end(), [](const candidate_solution& a, const candidate_solution& b)
	{
		return a.fitness < b.fitness;
	});
	const double range = pop[pop.size() - 1].fitness - pop[0].fitness;
	if (range == 0.0)
	{
		for (auto& p : pop)
		{
			p.affinity = 1.0;
		}
	}
	else
	{
		for (auto& p : pop)
		{
			p.affinity = 1.0 - p.fitness / range;
		}
	}
}

void clone_and_hyper_mutate(std::vector<candidate_solution>& clones,
                            std::vector<candidate_solution>& pop,
                            const double clone_factor)
{
	clones.clear();
	const auto i_num_clones = num_clones(pop.size(), clone_factor);
	calculate_affinity(pop);
	for (auto& antibody : pop)
	{
		const auto m_rate = calculate_mutation_rate(antibody);
		for (size_t i = 0; i < i_num_clones; ++i)
		{
			candidate_solution clone;
			point_mutation(clone.bit_string, antibody.bit_string, m_rate);
			clones.push_back(clone);
		}
	}
}

void random_insertion(std::vector<candidate_solution>& new_pop,
                      const std::vector<std::vector<double>>& search_space,
                      std::vector<candidate_solution>& pop,
                      const size_t num_rand,
                      const size_t bits_per_param)
{
	std::vector<candidate_solution> tmp_pop;
	if (num_rand == 0)
	{
		new_pop = pop;
		return;
	}
	std::vector<candidate_solution> rand_pop(num_rand);
	for (auto& r : rand_pop)
	{
		random_bit_string(r.bit_string, bits_per_param * search_space.size());
	}
	evaluate(rand_pop, search_space, bits_per_param);
	tmp_pop.resize(pop.size() + rand_pop.size());
	std::copy(pop.begin(), pop.end(), tmp_pop.begin());
	std::copy(rand_pop.begin(), rand_pop.end(), tmp_pop.begin() + pop.size());
	std::sort(tmp_pop.begin(), tmp_pop.end(), [](const candidate_solution& a, const candidate_solution& b)
	{
		return a.fitness < b.fitness;
	});
	tmp_pop.resize(pop.size());
	new_pop = tmp_pop;
}

void search(candidate_solution& best,
            const std::vector<std::vector<double>>& search_space,
            const size_t max_gens,
            const size_t pop_size,
            const double clone_factor,
            const size_t num_rand,
            const size_t bits_per_param = 16)
{
	std::vector<candidate_solution> pop(pop_size);
	for (auto& p : pop)
	{
		random_bit_string(p.bit_string, bits_per_param * search_space.size());
	}
	evaluate(pop, search_space, bits_per_param);
	std::sort(pop.begin(), pop.end(), [](const candidate_solution& a, const candidate_solution& b)
	{
		return a.fitness < b.fitness;
	});
	best = pop[0];
	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		std::vector<candidate_solution> clones;
		clone_and_hyper_mutate(clones, pop, clone_factor);
		evaluate(clones, search_space, bits_per_param);
		std::copy(clones.begin(), clones.end(), std::back_inserter(pop));
		std::sort(pop.begin(), pop.end(), [](const candidate_solution& a, const candidate_solution& b)
		{
			return a.fitness < b.fitness;
		});
		pop.resize(pop_size);
		random_insertion(pop, search_space, pop, num_rand, bits_per_param);
		std::vector<candidate_solution> new_pop;
		std::copy(pop.begin(), pop.end(), std::back_inserter(new_pop));
		new_pop.push_back(best);
		std::sort(new_pop.begin(), new_pop.end(), [](const candidate_solution& a, const candidate_solution& b)
		{
			return a.fitness < b.fitness;
		});
		best = new_pop[0];
		std::cout << "Generation: " << gen + 1 << " Best: " << best.fitness;
		for (const auto& v : best.vector)
		{
			std::cout << " " << v;
		}
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 2;
	std::vector<std::vector<double>> search_space(problem_size);
	for (auto& v : search_space)
	{
		v.push_back(-5);
		v.push_back(5);
	}
	// algorithm configuration
	const size_t max_gens = 100;
	const size_t pop_size = 100;
	const double clone_factor = 0.1;
	const size_t num_rand = 2;
	// execute the algorithm
	candidate_solution best;
	search(best, search_space, max_gens, pop_size, clone_factor, num_rand);
	std::cout << "done! Solution: f = " << best.fitness;
	for (auto& v : best.vector)
	{
		std::cout << " " << v;
	}
	std::cout << std::endl;
	return 0;
}
