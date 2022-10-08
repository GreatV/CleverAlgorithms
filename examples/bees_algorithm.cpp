#include <random>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>


using candidate_info = struct candidate_info_t
{
	std::vector<double> vector;
	double fitness = DBL_MAX;
};

std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

double objective_function(const std::vector<double>& x)
{
	return x[0] * x[0] + x[1] * x[1];
}

void random_vector(std::vector<double>& x,
                   const std::vector<std::vector<double>>& min_max)
{
	x.resize(min_max.size());
	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] = min_max[i][0] + random_double() * (min_max[i][1] - min_max[i][0]);
	}
}

void create_random_bee(std::vector<double>& x,
                       const std::vector<std::vector<double>>& search_space)
{
	random_vector(x, search_space);
}

void create_neigh_bee(candidate_info& bee,
                      const std::vector<double>& site,
                      const double patch_size,
                      const std::vector<std::vector<double>>& search_space)
{
	bee.vector.clear();
	for (size_t i = 0; i < site.size(); ++i)
	{
		auto v = site[i];
		v = random_double() < 0.5 ? v + random_double() * patch_size : v - random_double() * patch_size;
		if (v < search_space[i][0])
		{
			v = search_space[i][0];
		}
		if (v > search_space[i][1])
		{
			v = search_space[i][1];
		}
		bee.vector.push_back(v);
	}
}

bool cmp_fitness(const candidate_info& lhs, const candidate_info& rhs)
{
	return lhs.fitness < rhs.fitness;
}

void search_neigh(candidate_info& best,
                  const candidate_info& parent,
                  const size_t neigh_size,
                  const double patch_size,
                  const std::vector<std::vector<double>>& search_space)
{
	std::vector<candidate_info> neigh;
	for (size_t i = 0; i < neigh_size; ++i)
	{
		candidate_info bee;
		create_neigh_bee(bee, parent.vector, patch_size, search_space);
		bee.fitness = objective_function(bee.vector);
		neigh.push_back(bee);
	}
	std::sort(neigh.begin(), neigh.end(), cmp_fitness);
	best = neigh[0];
}

void create_scout_bees(std::vector<candidate_info>& bees,
                       const std::vector<std::vector<double>>& search_space,
                       const size_t num_scouts)
{
	for (size_t i = 0; i < num_scouts; ++i)
	{
		candidate_info bee;
		create_random_bee(bee.vector, search_space);
		bee.fitness = objective_function(bee.vector);
		bees.push_back(bee);
	}
}

void search(candidate_info& best,
            const size_t max_gens,
            const std::vector<std::vector<double>>& search_space,
            const size_t num_bees,
            const size_t num_sites,
            const size_t elite_sites,
            double patch_size,
            const size_t e_bees,
            const size_t o_bees)
{
	std::vector<candidate_info> pop(num_bees);
	for (auto& bee : pop)
	{
		create_random_bee(bee.vector, search_space);
		bee.fitness = objective_function(bee.vector);
	}
	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		std::sort(pop.begin(), pop.end(), cmp_fitness);
		if (gen == 0 || pop[0].fitness < best.fitness)
		{
			best = pop[0];
		}
		std::vector<candidate_info> next_gen;
		for (size_t i = 0; i < num_sites; ++i)
		{
			auto& parent = pop[i];
			const auto neigh_size = i < elite_sites ? e_bees : o_bees;
			candidate_info tmp;
			search_neigh(tmp, parent, neigh_size, patch_size, search_space);
			next_gen.push_back(tmp);
		}
		std::vector<candidate_info> scouts;
		create_scout_bees(scouts, search_space, num_bees - num_sites);
		pop.clear();
		pop.insert(pop.end(), next_gen.begin(), next_gen.end());
		pop.insert(pop.end(), scouts.begin(), scouts.end());
		patch_size = patch_size * 0.95;
		std::cout << " > it: " << gen << " patch size: " << patch_size
			<< "f = " << best.fitness << std::endl;
	}
}

int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 3;
	std::vector<std::vector<double>> search_space(problem_size);
	for (auto& bound : search_space)
	{
		bound.resize(2);
		bound[0] = -5.0;
		bound[1] = 5.0;
	}
	// algorithm configuration
	const size_t max_generations = 100;
	const size_t num_bees = 45;
	const size_t num_sites = 3;
	const size_t elite_sites = 1;
	const double patch_size = 3.0;
	const size_t e_bees = 7;
	const size_t o_bees = 2;
	// execute the algorithm
	candidate_info best;
	search(best, max_generations, search_space, num_bees, num_sites, elite_sites, patch_size, e_bees, o_bees);
	std::cout << "done! Solution: " << best.fitness;
	for (const auto& x : best.vector)
	{
		std::cout << " " << x;
	}
	std::cout << std::endl;
}
