#include <random>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random = []() { return distribution(generator); };

using prob_info = struct prob_info_t
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
	double sum = 0;
	for (size_t i = 0; i < x.size(); ++i)
	{
		sum += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return sqrt(sum);
}

double cost(const std::vector<size_t>& permutation,
            const std::vector<std::vector<double>>& cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < permutation.size(); ++i)
	{
		auto& c1 = permutation[i];
		auto& c2 = i == permutation.size() - 1 ? permutation[0] : permutation[i + 1];
		distance += euc_2d(cities[c1], cities[c2]);
	}
	return distance;
}

void random_permutation(std::vector<size_t>& permutation,
                        const std::vector<std::vector<double>>& cities)
{
	permutation.resize(cities.size());
	for (size_t i = 0; i < permutation.size(); ++i)
	{
		permutation[i] = i;
	}
	for (size_t i = 0; i < permutation.size(); ++i)
	{
		const auto r = static_cast<size_t>(random() * (permutation.size() - i)) + i;
		std::swap(permutation[i], permutation[r]);
	}
}

void initialise_pheromone(std::vector<std::vector<double>>& pheromone,
                          const size_t num_cities, const double initial_pheromone)
{
	pheromone.resize(num_cities);
	for (size_t i = 0; i < num_cities; ++i)
	{
		pheromone[i].resize(num_cities);
		for (size_t j = 0; j < num_cities; ++j)
		{
			pheromone[i][j] = initial_pheromone;
		}
	}
}

void calculate_choices(std::vector<prob_info>& choices,
                       const std::vector<std::vector<double>>& cities,
                       const size_t last_city,
                       const std::vector<size_t>& exclude,
                       const std::vector<std::vector<double>>& pheromone,
                       const double c_heuristic,
                       const double c_history)
{
	choices.clear();

	for (size_t i = 0; i < cities.size(); ++i)
	{
		auto coordinate = cities[i];
		if (std::find(exclude.begin(), exclude.end(), i) != exclude.end())
		{
			continue;
		}
		prob_info prob;
		prob.city = i;
		prob.history = pow(pheromone[last_city][i], c_history);
		prob.distance = euc_2d(cities[last_city], coordinate);
		prob.heuristic = pow(1.0 / prob.distance, c_heuristic);
		prob.probability = prob.history * prob.heuristic;
		choices.push_back(prob);
	}
}

size_t prob_selection(const std::vector<prob_info>& choices)
{
	double sum = 0.0;
	for (auto& choice : choices)
	{
		sum += choice.probability;
	}
	if (sum == 0.0)
	{
		const auto random_index = static_cast<size_t>(random() * (choices.size() - 1));
		return choices[random_index].city;
	}
	double v = random();
	for (const auto& choice : choices)
	{
		v -= choice.probability / sum;
		if (v <= 0.0)
		{
			return choice.city;
		}
	}
	return choices[choices.size() - 1].city;
}

size_t greedy_select(const std::vector<prob_info>& choices)
{
	double min_cost = DBL_MAX;
	size_t min_index = 0;
	for (size_t i = 0; i < choices.size(); ++i)
	{
		if (choices[i].cost < min_cost)
		{
			min_cost = choices[i].cost;
			min_index = i;
		}
	}
	return choices[min_index].city;
}

void stepwise_const(std::vector<size_t>& permutation,
                    const std::vector<std::vector<double>>& cities,
                    const std::vector<std::vector<double>>& pheromone,
                    const double c_heuristic,
                    const double c_greed)
{
	permutation.clear();
	const auto random_index = static_cast<size_t>(random() * (cities.size() - 1));
	permutation.push_back(random_index);
	while (permutation.size() < cities.size())
	{
		std::vector<prob_info> choices;
		calculate_choices(choices, cities, permutation.back(), permutation, pheromone, c_heuristic, c_greed);
		const auto greedy = random() < c_greed;
		auto next_city = greedy ? greedy_select(choices) : prob_selection(choices);
		permutation.push_back(next_city);
	}
}

void global_update_pheromone(std::vector<std::vector<double>>& pheromone,
                             const candidate_info& candidate,
                             const double decay)
{
	for (size_t i = 0; i < candidate.vector.size(); ++i)
	{
		auto& x = candidate.vector[i];
		auto& y = i == candidate.vector.size() - 1 ? candidate.vector[0] : candidate.vector[i + 1];
		pheromone[x][y] = (1.0 - decay) * pheromone[x][y] + decay * 1.0 / candidate.cost;
		pheromone[y][x] = pheromone[x][y];
	}
}

void local_update_pheromone(std::vector<std::vector<double>>& pheromone,
                            const candidate_info& candidate,
                            const double c_local_pheromone,
                            const double init_pheromone)
{
	for (size_t i = 0; i < candidate.vector.size(); ++i)
	{
		auto& x = candidate.vector[i];
		auto& y = i == candidate.vector.size() - 1 ? candidate.vector[0] : candidate.vector[i + 1];
		pheromone[x][y] = (1.0 - c_local_pheromone) * pheromone[x][y] + c_local_pheromone * init_pheromone;
		pheromone[y][x] = pheromone[x][y];
	}
}

void search(candidate_info& best,
            const std::vector<std::vector<double>>& cities,
            const size_t max_it,
            const size_t num_ants,
            const double decay,
            const double c_heuristic,
            const double c_local_pheromone,
            const double c_greed)
{
	random_permutation(best.vector, cities);
	best.cost = cost(best.vector, cities);
	const auto init_pheromone = 1.0 / (cities.size() * best.cost);
	std::vector<std::vector<double>> pheromone;
	initialise_pheromone(pheromone, cities.size(), init_pheromone);
	for (size_t iteration = 0; iteration < max_it; ++iteration)
	{
		for (size_t i = 0; i < num_ants; ++i)
		{
			candidate_info candidate;
			stepwise_const(candidate.vector, cities, pheromone, c_heuristic, c_greed);
			candidate.cost = cost(candidate.vector, cities);
			if (candidate.cost < best.cost)
			{
				best = candidate;
			}
			local_update_pheromone(pheromone, candidate, c_local_pheromone, init_pheromone);
		}
		global_update_pheromone(pheromone, best, decay);
		std::cout << "Iteration " << iteration + 1 << ", best = " << best.cost << std::endl;
	}
}


int main(int argc, char* argv[])
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
	const size_t max_it = 100;
	const size_t num_ants = 10;
	const double decay = 0.1;
	const double c_heuristic = 2.5;
	const double c_local_phero = 0.1;
	const double c_greed = 0.9;
	// execute the algorithm
	candidate_info best;
	search(best, berlin52, max_it, num_ants, decay, c_heuristic, c_local_phero, c_greed);
	std::cout << " > Done. Best Solution: c = " << best.cost << ", v = ";
	for (const auto& city : best.vector)
	{
		std::cout << city << " ";
	}
	std::cout << std::endl;
	return 0;
}
