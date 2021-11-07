#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_st
{
	std::vector<size_t> vector;
	double cost = 0.0;
};


double euc_2d(const std::vector<double>& c1, const std::vector<double>& c2)
{
	double sum = 0.0;
	for (size_t i = 0; i < c1.size(); ++i)
	{
		sum += (c1[i] - c2[i]) * (c1[i] - c2[i]);
	}

	return sqrt(sum);
}


double cost(const std::vector<size_t>& permutation, const std::vector<std::vector<double>>& cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < permutation.size(); ++i)
	{
		const auto c1 = permutation[i];
		const auto c2 = (i == permutation.size() - 1) ? permutation[0] : permutation[i + 1];
		distance += euc_2d(cities[c1], cities[c2]);
	}

	return distance;
}


void random_permutation(std::vector<size_t>& perm, const std::vector<std::vector<double>>& cities)
{
	perm.resize(cities.size());
	for (size_t i = 0; i < cities.size(); ++i)
	{
		perm[i] = i;
	}

	for (size_t i = 0; i < perm.size(); ++i)
	{
		const auto r = static_cast<size_t>(random_() * (perm.size() - 1 - i)) + i;
		const auto tmp = perm[r];
		perm[r] = perm[i];
		perm[i] = tmp;
	}
}


void stochastic_two_opt(std::vector<size_t>& perm)
{
	auto c1 = static_cast<size_t>(random_() * (perm.size() - 1));
	auto c2 = static_cast<size_t>(random_() * (perm.size() - 1));
	std::vector<size_t> exclude;
	exclude.push_back(c1);
	exclude.push_back(c1 == 0 ? perm.size() - 1 : c1 - 1);
	exclude.push_back(c1 == perm.size() - 1 ? 0 : c1 + 1);
	while (std::find(exclude.begin(), exclude.end(), c2) != exclude.end())
	{
		c2 = static_cast<size_t>(random_() * (perm.size() - 1));
	}
	if (c2 < c1)
	{
		const auto tmp = c1;
		c1 = c2;
		c2 = tmp;
	}

	for (size_t i = c1; i < (c2 - c1) / 2; ++i)
	{
		const auto tmp = perm[c1];
		perm[c1] = perm[c2];
		perm[c2] = tmp;
	}
}


void create_neighbor(candidate_solution& candidate, const candidate_solution& current,
                     const std::vector<std::vector<double>>& cities)
{
	candidate.vector.clear();
	candidate.vector = current.vector;

	stochastic_two_opt(candidate.vector);
	candidate.cost = cost(candidate.vector, cities);
}


bool should_accept(const candidate_solution& candidate, const candidate_solution& current,
                   const double temp)
{
	if (candidate.cost <= current.cost)
	{
		return true;
	}

	const auto tmp = exp((current.cost - candidate.cost) / temp);

	return tmp > random_();
}


void search(candidate_solution& best,
            const std::vector<std::vector<double>>& cities,
            const size_t max_iter,
            const double max_temp,
            const double temp_change)
{
	candidate_solution current;
	random_permutation(current.vector, cities);
	current.cost = cost(current.vector, cities);

	auto temp = max_temp;
	best = current;
	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		candidate_solution candidate;
		create_neighbor(candidate, current, cities);
		temp = temp * temp_change;
		if (should_accept(candidate, current, temp))
		{
			current = candidate;
		}
		if (candidate.cost < best.cost)
		{
			best = candidate;
		}

		if ((iter + 1) % 10 == 0)
		{
			std::cout << " > iteration " << iter + 1<< ", temp = " << temp
				<< ", best = " << best.cost << std::endl;
		}
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const std::vector<std::vector<double>> berlin52 = {
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
	const size_t max_iterations = 2000;
	const double max_temp = 1e5;
	const double temp_change = 0.98;
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, max_iterations, max_temp, temp_change);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (unsigned int i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
