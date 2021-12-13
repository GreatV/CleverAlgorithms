#include <cmath>
#include <vector>
#include <cfloat>
#include <iostream>
#include <algorithm>


double random(const double min, const double max)
{
	return min + (max - min) * rand() / RAND_MAX;
}

using probabilistic_info = struct probabilistic_info_t
{
	double history = 0.0;
	double probability = 0.0;
	double distance = 0.0;
	double heuristic = 0.0;
	double prob = 0.0;
	double cost = 0.0;
	size_t city = 0;
};

using candidate_info = struct candidate_info_t
{
	std::vector<size_t> vector;
	double cost = DBL_MAX;
};


double euc_2d(const std::vector<double>& x, const std::vector<double>& y)
{
	double sum = 0.0;
	for (size_t i = 0; i < x.size(); i++)
	{
		sum += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return sqrt(sum);
}

double cost(const std::vector<size_t>& permutation, const std::vector<std::vector<double>>& cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < permutation.size(); i++)
	{
		auto& c1 = permutation[i];
		auto& c2 = i == permutation.size() - 1 ? permutation[0] : permutation[i + 1];
		distance += euc_2d(cities[c1], cities[c2]);
	}
	return distance;
}

void random_permutation(std::vector<size_t>& permutation, const size_t size)
{
	permutation.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		permutation[i] = i;
	}
	for (size_t i = 0; i < size; i++)
	{
		const size_t j = rand() % size;
		std::swap(permutation[i], permutation[j]);
	}
}

void initialise_pheromone_matrix(std::vector<std::vector<double>>& pheromone_matrix, const size_t size,
                                 const double naive_score)
{
	const auto v = size / naive_score;
	pheromone_matrix.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		pheromone_matrix[i].resize(size);
		for (size_t j = 0; j < size; j++)
		{
			pheromone_matrix[i][j] = v;
		}
	}
}

void calculate_choices(std::vector<probabilistic_info>& choices,
                       const std::vector<std::vector<double>>& cities,
                       const size_t last_city,
                       const std::vector<size_t>& exclude,
                       const std::vector<std::vector<double>>& pheromone_matrix,
                       const double c_heur,
                       const double c_hist)
{
	choices.clear();
	for (size_t i = 0; i < cities.size(); i++)
	{
		auto& coord = cities[i];
		if (std::find(exclude.begin(), exclude.end(), i) != exclude.end())
		{
			continue;
		}
		probabilistic_info prob;
		prob.city = i;
		prob.history = pow(pheromone_matrix[last_city][i], c_hist);
		prob.distance = euc_2d(cities[last_city], coord);
		prob.heuristic = pow(1.0 / prob.distance, c_heur);
		prob.prob = prob.history * prob.heuristic;
		choices.push_back(prob);
	}
}

size_t select_next_city(const std::vector<probabilistic_info>& choices)
{
	double sum = 0.0;
	for (auto& c : choices)
	{
		sum += c.prob;
	}
	if (sum == 0.0)
	{
		return choices[rand() % choices.size()].city;
	}
	auto v = random(0.0, 1.0);
	for (const auto& choice : choices)
	{
		v -= choice.prob / sum;
		if (v <= 0.0)
		{
			return choice.city;
		}
	}
	auto& choice = choices[choices.size() - 1];
	return choice.city;
}

void stepwise_const(
	std::vector<size_t>& permutation,
	const std::vector<std::vector<double>>& cities,
	const std::vector<std::vector<double>>& pheromone_matrix,
	const double c_heur,
	const double c_hist)
{
	permutation.clear();
	permutation.push_back(rand() % cities.size());
	while (permutation.size() < cities.size())
	{
		std::vector<probabilistic_info> choices;
		calculate_choices(choices, cities, permutation.back(), permutation, pheromone_matrix, c_heur, c_hist);
		permutation.push_back(select_next_city(choices));
	}
}

void decay_pheromone(std::vector<std::vector<double>>& pheromone_matrix, const double decay_rate)
{
	for (size_t i = 0; i < pheromone_matrix.size(); i++)
	{
		for (size_t j = 0; j < pheromone_matrix[0].size(); j++)
		{
			pheromone_matrix[i][j] *= 1.0 - decay_rate;
		}
	}
}

void update_pheromone(std::vector<std::vector<double>>& pheromone_matrix, const std::vector<candidate_info>& solutions)
{
	for (auto& other : solutions)
	{
		for (size_t i = 0; i < other.vector.size(); i++)
		{
			auto& x = other.vector[i];
			auto& y = i == other.vector.size() - 1 ? other.vector[0] : other.vector[i + 1];
			pheromone_matrix[x][y] += other.cost;
			pheromone_matrix[y][x] += other.cost;
		}
	}
}

void search(candidate_info& best,
            const std::vector<std::vector<double>>& cities,
            const size_t max_it,
            const size_t num_ants,
            const double decay_factor,
            const double c_heur,
            const double c_hist)
{
	random_permutation(best.vector, cities.size());
	best.cost = cost(best.vector, cities);
	std::vector<std::vector<double>> pheromone;
	initialise_pheromone_matrix(pheromone, cities.size(), best.cost);
	for (size_t iter = 0; iter < max_it; iter++)
	{
		std::vector<candidate_info> solutions;
		for (size_t i = 0; i < num_ants; i++)
		{
			candidate_info candidate;
			stepwise_const(candidate.vector, cities, pheromone, c_heur, c_hist);
			candidate.cost = cost(candidate.vector, cities);
			solutions.push_back(candidate);
			if (candidate.cost < best.cost)
			{
				best = candidate;
			}
		}
		decay_pheromone(pheromone, decay_factor);
		update_pheromone(pheromone, solutions);
		std::cout << " > Iteration: " << iter + 1 << " Best: " << best.cost << std::endl;
	}
}


int main(int argc, char** argv)
{
	// problem configuration
	const std::vector<std::vector<double>> berlin52 = {
		{565, 575}, {25, 185}, {345, 750}, {945, 685}, {845, 655},
		{880, 660}, {25, 230}, {525, 1000}, {580, 1175}, {650, 1130},
		{1605, 620}, {1220, 580}, {1465, 200}, {1530, 5}, {845, 680},
		{725, 370}, {145, 665}, {415, 635}, {510, 875}, {560, 365},
		{300, 465}, {520, 585}, {480, 415}, {835, 625}, {975, 580},
		{1215, 245}, {1320, 315}, {1250, 400}, {660, 180}, {410, 250},
		{420, 555}, {575, 665}, {1150, 1160}, {700, 580}, {685, 595},
		{685, 610}, {770, 610}, {795, 645}, {720, 635}, {760, 650},
		{475, 960}, {95, 260}, {875, 920}, {700, 500}, {555, 815},
		{830, 485}, {1170, 65}, {830, 610}, {605, 625}, {595, 360},
		{1340, 725}, {1740, 245}
	};
	// algorithm configuration
	const size_t max_it = 50;
	const size_t num_ants = 30;
	const double decay_factor = 0.6;
	const double c_heur = 2.5;
	const double c_hist = 1.0;
	// execute the algorithm
	candidate_info best;
	search(best, berlin52, max_it, num_ants, decay_factor, c_heur, c_hist);
	std::cout << "Done. Best Solution:  c = " << best.cost << " V = ";
	for (const auto& city : best.vector)
	{
		std::cout << " " << city;
	}
	std::cout << std::endl;

	return 0;
}
