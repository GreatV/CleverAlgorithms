#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::vector<size_t> vector;
	double cost = 0.0;
};


double euc_2d(std::vector<double>& c1, std::vector<double>& c2)
{
	return sqrt((c1[0] - c2[0]) * (c1[0] - c2[0]) + (c1[1] - c2[1]) * (c1[1] - c2[1]));
}


double cost(std::vector<size_t>& perm, std::vector<std::vector<double>> cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < perm.size(); ++i)
	{
		const auto c1 = perm[i];
		const auto c2 = (i == perm.size() - 1) ? perm[0] : perm[i + 1];
		distance += euc_2d(cities[c1], cities[c2]);
	}
	return distance;
}


void random_permutation(std::vector<size_t>& perm, std::vector<std::vector<double>>& cities)
{
	perm.resize(cities.size());
	for (size_t i = 0; i < cities.size(); ++i)
	{
		perm[i] = i;
	}
	for (size_t i = 0; i < perm.size(); ++i)
	{
		const auto r = static_cast<size_t>((perm.size() - 1 - i) * random_() + i);
		const auto tmp = perm[r];
		perm[r] = perm[i];
		perm[i] = tmp;
	}
}


void stochastic_two_opt(std::vector<size_t>& perm)
{
	auto c1 = static_cast<size_t>((perm.size() - 1) * random_());
	auto c2 = static_cast<size_t>((perm.size() - 1) * random_());

	std::vector<size_t> exclude;
	exclude.push_back(c1);
	exclude.push_back(c1 == 0 ? perm.size() - 1 : c1 - 1);
	exclude.push_back(c1 == perm.size() - 1 ? 0 : c1 + 1);
	while (std::find(exclude.begin(), exclude.end(), c2) != exclude.end())
	{
		c2 = static_cast<size_t>((perm.size() - 1) * random_());
	}

	if (c2 < c1)
	{
		const size_t tmp = c1;
		c1 = c2;
		c2 = tmp;
	}

	for (size_t i = c1; i < (c2 - c1) / 2; ++i)
	{
		const size_t tmp = perm[i];
		perm[i] = perm[c2 - 1 - i + c1];
		perm[c2 - 1 - i + c1] = tmp;
	}
}


void local_search(candidate_solution& best, std::vector<std::vector<double>>& cities, const size_t max_no_improv,
                  const size_t neighborhood)
{
	size_t count = 0;
	while (count < max_no_improv)
	{
		candidate_solution candidate;
		candidate.vector = best.vector;
		for (size_t i = 0; i < neighborhood; ++i)
		{
			stochastic_two_opt(candidate.vector);
		}
		candidate.cost = cost(candidate.vector, cities);
		if (candidate.cost < best.cost)
		{
			best.vector = candidate.vector;
			best.cost = candidate.cost;

			count = 0;
		}
		else
		{
			count += 1;
		}
	}
}


void search(candidate_solution& best, std::vector<std::vector<double>>& cities,
            std::vector<size_t>& neighborhoods, const size_t max_no_improv, const size_t max_no_improv_ls)
{
	random_permutation(best.vector, cities);
	best.cost = cost(best.vector, cities);
	size_t iter = 0, count = 0;

	while (count < max_no_improv)
	{
		for (unsigned int neigh : neighborhoods)
		{
			candidate_solution candidate;
			candidate.vector = best.vector;
			for (size_t j = 0; j < neigh; ++j)
			{
				stochastic_two_opt(candidate.vector);
			}
			candidate.cost = cost(candidate.vector, cities);
			local_search(candidate, cities, max_no_improv_ls, neigh);
			std::cout << " > iteration " << iter + 1
				<< ", neigh = " << neigh
				<< ", best = " << best.cost << std::endl;
			iter += 1;

			if (candidate.cost < best.cost)
			{
				best.vector = candidate.vector;
				best.cost = candidate.cost;
				count = 0;
				std::cout << "New best, restarting neighborhood search." << std::endl;
				break;
			}
			count += 1;
		}
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	std::vector<std::vector<double>> berlin52 = {
		{565, 575}, {25, 185}, {345, 750}, {945, 685}, {845, 655},
		{880, 660}, {25, 230}, {525, 1000}, {580, 1175}, {650, 1130}, {1605, 620},
		{1220, 580}, {1465, 200}, {1530, 5}, {845, 680}, {725, 370}, {145, 665},
		{415, 635}, {510, 875}, {560, 365}, {300, 465}, {520, 585}, {480, 415},
		{835, 625}, {975, 580}, {1215, 245}, {1320, 315}, {1250, 400}, {660, 180},
		{410, 250}, {420, 555}, {575, 665}, {1150, 1160}, {700, 580}, {685, 595},
		{685, 610}, {770, 610}, {795, 645}, {720, 635}, {760, 650}, {475, 960},
		{95, 260}, {875, 920}, {700, 500}, {555, 815}, {830, 485}, {1170, 65},
		{830, 610}, {605, 625}, {595, 360}, {1340, 725}, {1740, 245}
	};
	// algorithm configuration
	const size_t max_no_improv = 20;
	const size_t max_no_improv_ls = 70;
	std::vector<size_t> neighborhoods;
	for (size_t i = 0; i < 30; ++i)
	{
		neighborhoods.push_back(1 + i);
	}
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, neighborhoods, max_no_improv, max_no_improv_ls);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (auto & i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
