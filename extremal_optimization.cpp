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


using neighbor_info = struct neighbor_info_st
{
	size_t number = 0;
	double distance = 0.0;
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


bool cmp_distance(const neighbor_info & l, const neighbor_info & r)
{
	if (l.distance < r.distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void calculate_neighbor_rank(std::vector<neighbor_info> & neighbors,
	const size_t city_number,
	const std::vector<std::vector<double>> & cities,
	const std::vector<size_t> & ignore)
{
	for(size_t i = 0; i < cities.size(); ++i)
	{
		auto &  city = cities[i];
		if(i == city_number || std::find(ignore.begin(), ignore.end(), i) != ignore.end())
		{
			continue;
		}
		neighbor_info neighbor;
		neighbor.number = i;
		neighbor.distance = euc_2d(cities[city_number], city);
		neighbors.push_back(neighbor);
	}

	std::sort(neighbors.begin(), neighbors.end(), cmp_distance);
}


void get_edges_for_city(size_t & c1, size_t & c2, const size_t city_number, 
	const std::vector<size_t> & permutation)
{
	for(size_t i = 0; i < permutation.size(); ++i)
	{
		auto c = permutation[i];
		if (c == city_number)
		{
			c1 = (i == 0) ? *(permutation.end() - 1) : permutation[i - 1];
			c2 = (i == permutation.size() - 1) ? permutation[0] : permutation[i + 1];
			break;
		}
	}
}


double calculate_city_fitness(const std::vector<size_t> & permutation,
	const size_t city_number,
	const std::vector<std::vector<double>> & cities)
{
	size_t c1, c2;
	get_edges_for_city(c1, c2, city_number, permutation);
	std::vector<neighbor_info> neighbors;
	std::vector<size_t> ignore;
	calculate_neighbor_rank(neighbors, city_number, cities, ignore);
	long long n1 = -1, n2 = -1;
	for(size_t i = 0; i < neighbors.size(); ++i)
	{
		const auto & neighbor = neighbors[i];
		if (neighbor.number == c1)
			n1 = i + 1;
		if (neighbor.number == c2)
			n2 = i + 1;
		if (n1 != -1 && n2 != -1)
			break;
	}

	return 3.0 / static_cast<double>(n1 + n2);
}


void calculate_city_fitnesses()
{
	
}


void search()
{
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
	const size_t max_iterations = 250;
	const double tau = 1.8;
	// execute the algorithm
	candidate_solution best;
	search();

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (unsigned int i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
