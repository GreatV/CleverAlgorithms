#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cfloat>
#include <iostream>


using candidate_info = struct candidate_info_t
{
	std::vector<double> position;
	std::vector<double> b_position;
	double b_cost = DBL_MAX;
	std::vector<double> velocity;
	double cost = DBL_MAX;
};

double objective_function(const std::vector<double>& x)
{
	double sum = 0.0;
	for (const auto& xi : x)
	{
		sum += xi * xi;
	}
	return sum;
}

double random(const double min, const double max)
{
	return min + (max - min) * rand() / RAND_MAX;
}

void random_vector(std::vector<double>& x,
                   const std::vector<std::vector<double>>& search_space)
{
	x.clear();
	x.resize(search_space.size());
	for (size_t i = 0; i < x.size(); i++)
	{
		x[i] = random(search_space[i][0], search_space[i][1]);
	}
}

void create_particle(candidate_info& particle,
                     const std::vector<std::vector<double>>& search_space,
                     const std::vector<std::vector<double>>& velocity_space)
{
	random_vector(particle.position, search_space);
	particle.cost = objective_function(particle.position);
	particle.b_position = particle.position;
	particle.b_cost = particle.cost;
	random_vector(particle.velocity, velocity_space);
}

bool cmp_cost(const candidate_info& a, const candidate_info& b)
{
	return a.cost < b.cost;
}

void get_global_best(candidate_info& current_best, std::vector<candidate_info>& population)
{
	std::sort(population.begin(), population.end(), cmp_cost);
	candidate_info best;
	best.position = population[0].position;
	best.cost = population[0].cost;

	if (best.cost < current_best.cost)
	{
		current_best.position = best.position;
		current_best.cost = best.cost;
	}
}

void update_velocity(candidate_info& particle,
                     const candidate_info& g_best,
                     const double max_velocity,
                     const double c1, const double c2)
{
	for (size_t i = 0; i < particle.velocity.size(); i++)
	{
		const auto& v = particle.velocity[i];
		const auto v1 = c1 * random(0.0, 1.0) * (particle.b_position[i] - particle.position[i]);
		const auto v2 = c2 * random(0.0, 1.0) * (g_best.position[i] - particle.position[i]);
		particle.velocity[i] = v + v1 + v2;
		particle.velocity[i] = std::min(max_velocity, particle.velocity[i]);
		particle.velocity[i] = std::max(-max_velocity, particle.velocity[i]);
	}
}

void update_position(candidate_info& particle,
                     const std::vector<std::vector<double>>& search_space)
{
	for (size_t i = 0; i < particle.position.size(); i++)
	{
		particle.position[i] += particle.velocity[i];

		if (particle.position[i] > search_space[i][1])
		{
			particle.position[i] = search_space[i][1] - abs(particle.position[i] - search_space[i][1]);
			particle.velocity[i] = -particle.velocity[i];
		}

		if (particle.position[i] < search_space[i][0])
		{
			particle.position[i] = search_space[i][0] + abs(particle.position[i] - search_space[i][0]);
			particle.velocity[i] = -particle.velocity[i];
		}
	}
}

void update_best_position(candidate_info& particle)
{
	if (particle.cost < particle.b_cost)
	{
		particle.b_position = particle.position;
		particle.b_cost = particle.cost;
	}
}

void search(
	candidate_info& g_best,
	const size_t max_generations,
	const std::vector<std::vector<double>>& search_space,
	const std::vector<std::vector<double>>& velocity_space,
	const size_t population_size,
	const double max_velocity,
	const double c1, const double c2)
{
	std::vector<candidate_info> population;
	population.resize(population_size);
	for (size_t i = 0; i < population_size; i++)
	{
		create_particle(population[i], search_space, velocity_space);
	}
	std::sort(population.begin(), population.end(), cmp_cost);
	g_best.position = population[0].position;
	g_best.cost = objective_function(g_best.position);

	for (size_t i = 0; i < max_generations; i++)
	{
		for (size_t j = 0; j < population_size; j++)
		{
			auto& particle = population[j];
			update_velocity(particle, g_best, max_velocity, c1, c2);
			update_position(particle, search_space);
			particle.cost = objective_function(particle.position);
			update_best_position(particle);
		}
		get_global_best(g_best, population);
		std::cout << " > Generation: " << i + 1 << " fitness: " << g_best.cost << std::endl;
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
	std::vector<std::vector<double>> velocity_space(problem_size);
	for (auto& bound : velocity_space)
	{
		bound.resize(2);
		bound[0] = -1.0;
		bound[1] = 1.0;
	}
	const size_t max_generations = 100;
	const size_t population_size = 100;
	const double max_velocity = 100.0;
	const double c1 = 2.0, c2 = 2.0;
	// execute the algorithm
	candidate_info g_best;
	search(g_best, max_generations, search_space, velocity_space, population_size, max_velocity, c1, c2);
	std::cout << "done! Solution: " << g_best.cost;
	for (auto& x : g_best.position)
	{
		std::cout << " " << x;
	}
	std::cout << std::endl;
}
