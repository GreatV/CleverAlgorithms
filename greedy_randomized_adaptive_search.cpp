#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() {return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::vector<size_t> vector;
	double cost = 0.0;
};


double euc_2d(std::vector<double> & c1, std::vector<double> & c2)
{
	return sqrt((c1[0] - c2[0]) * (c1[0] - c2[0]) + (c1[1] - c2[1]) * (c1[1] - c2[1]));
}


double cost(std::vector<size_t> & perm, std::vector<std::vector<double> > cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < perm.size(); ++i)
	{
		size_t c1 = perm[i];
		size_t c2 = (i == perm.size() - 1) ? perm[0] : perm[i + 1];
		distance += euc_2d(cities[c1], cities[c2]);
	}
	return distance;
}


void stochastic_two_opt(std::vector<size_t> & perm, std::vector<size_t> & permutation)
{
	perm.resize(permutation.size());
	perm.assign(permutation.begin(), permutation.end());

	size_t c1 = (size_t)((perm.size() - 1) * random_());
	size_t c2 = (size_t)((perm.size() - 1) * random_());

	std::vector<size_t> exclude;
	exclude.push_back(c1);
	exclude.push_back(c1 == 0 ? perm.size() - 1 : c1 - 1);
	exclude.push_back(c1 == perm.size() - 1 ? 0 : c1 + 1);
	while (std::find(exclude.begin(), exclude.end(), c2) != exclude.end())
	{
		c2 = (size_t)((perm.size() - 1) * random_());
	}

	if (c2 < c1)
	{
		size_t tmp = c1;
		c1 = c2;
		c2 = tmp;
	}

	for (size_t i = c1; i < (c2 - c1) / 2; ++i)
	{
		size_t tmp = perm[i];
		perm[i] = perm[c2 - 1 - i + c1];
		perm[c2 - 1 - i + c1] = tmp;
	}
}


void local_search(candidate_solution & best, std::vector<std::vector<double> > & cities, size_t max_no_improv)
{
	size_t count = 0;
	while (count < max_no_improv)
	{
		candidate_solution candidate;
		stochastic_two_opt(candidate.vector, best.vector);
		candidate.cost = cost(candidate.vector, cities);
		count = candidate.cost < best.cost ? 0 : count + 1;
		if (candidate.cost < best.cost)
		{
			best.vector = candidate.vector;
			best.cost = candidate.cost;
		}
	}
}


void construct_randomized_greedy_solution(candidate_solution & candidate, std::vector<std::vector<double> > & cities, double alpha)
{
	candidate.vector.clear();
	candidate.vector.push_back((size_t)((cities.size() - 1) * random_()));

	std::vector<size_t> allCities;
	for (size_t i = 0; i < cities.size(); ++i)
	{
		allCities.push_back(i);
	}

	while (candidate.vector.size() < cities.size())
	{
		std::vector<size_t> sorted_candidate(candidate.vector);
		std::sort(sorted_candidate.begin(), sorted_candidate.end());
		std::vector<size_t> candidates;
		std::set_difference(allCities.begin(), allCities.end(),sorted_candidate.begin(), sorted_candidate.end(), std::inserter(candidates, candidates.begin()));

		std::vector<double> costs;
		costs.resize(candidates.size());
		for (size_t i = 0; i < candidates.size(); ++i)
		{
			costs[i] = euc_2d(cities[*(candidate.vector.end() - 1)], cities[i]);
		}
		std::vector<size_t> rcl;
		double max = *std::max_element(costs.begin(), costs.end());
		double min = *std::min_element(costs.begin(), costs.end());
		for (size_t i = 0; i < costs.size(); ++i)
		{
			double c = costs[i];
			if (c <= min + alpha * (max - min))
				rcl.push_back(candidates[i]);
		}
		candidate.vector.push_back(rcl[(size_t)((rcl.size() - 1)*random_())]);
	}
	candidate.cost = cost(candidate.vector, cities);
}


void search(candidate_solution & best, std::vector<std::vector<double> > & cities,
	size_t max_iter, size_t max_no_improv, double alpha)
{
	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		candidate_solution candidate;
		construct_randomized_greedy_solution(candidate, cities, alpha);
		local_search(candidate, cities, max_no_improv);
		if (iter == 0)
		{
			best = candidate;
		}
		else
		{
			if (candidate.cost < best.cost)
			{
				best = candidate;
			}
		}
		std::cout << " > iteration "<< (iter+1) <<", best=" << best.cost << std::endl;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	std::vector<std::vector<double> > berlin52 = {
		{565,575},{25,185},{345,750},{945,685},{845,655},
		{880,660},{25,230},{525,1000},{580,1175},{650,1130},{1605,620},
		{1220,580},{1465,200},{1530,5},{845,680},{725,370},{145,665},
		{415,635},{510,875},{560,365},{300,465},{520,585},{480,415},
		{835,625},{975,580},{1215,245},{1320,315},{1250,400},{660,180},
		{410,250},{420,555},{575,665},{1150,1160},{700,580},{685,595},
		{685,610},{770,610},{795,645},{720,635},{760,650},{475,960},
		{95,260},{875,920},{700,500},{555,815},{830,485},{1170,65},
		{830,610},{605,625},{595,360},{1340,725},{1740,245}
	};
	// algorithm configuration
	const size_t max_iter = 50;
	const size_t max_no_improv = 50;
	const size_t greediness_factor = 70;
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, max_iter, max_no_improv, greediness_factor);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (size_t i = 0; i < best.vector.size(); ++i)
		std::cout << best.vector[i] << " ";
	std::cout << "}" << std::endl;

	return 0;
}
