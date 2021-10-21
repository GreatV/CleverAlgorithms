#include <iostream>
#include <numeric>
#include <random>
#include <vector>
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


double cost(std::vector<size_t> & permutation, std::vector<std::vector<double> > & cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < permutation.size(); ++i)
	{
		size_t c1 = permutation[i];
		size_t c2 = i == permutation.size() - 1 ? permutation[0] : permutation[i + 1];
		distance += euc_2d(cities[c1], cities[c2]);
	}
	return distance;
}


void random_permutation(std::vector<size_t> & perm, std::vector<std::vector<double> > & cities)
{
	perm.resize(cities.size());
	for (size_t i = 0; i < cities.size(); ++i)
	{
		perm[i] = i;
	}
	for (size_t i = 0; i < perm.size(); ++i)
	{
		size_t r = (size_t)((perm.size() - 1 - i) * random_() + i);
		size_t tmp = perm[r];
		perm[r] = perm[i];
		perm[i] = tmp;
	}
}


void stochastic_two_opt(std::vector<size_t> & perm, std::vector<size_t> & permutation)
{
	perm.resize(permutation.size());
	perm = permutation;
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

	for (size_t i = c1; i < c2; ++i)
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
		count = (candidate.cost < best.cost) ? 0 : count + 1;
		if (candidate.cost < best.cost)
		{
			best = candidate;
		}
	}
}


void double_bridge_move(std::vector<size_t> & p, std::vector<size_t> & perm)
{
	p.clear();
	size_t pos1 = (size_t)(1 + (perm.size() / 4 - 1) * random_());
	size_t pos2 = (size_t)(pos1 + 1 + (perm.size() / 4 - 1) * random_());
	size_t pos3 = (size_t)(pos2 + 1 + (perm.size() / 4 - 1) * random_());
	for (size_t i = 0; i < pos1; ++i)
	{
		p.push_back(perm[i]);
	}
	for (size_t i = pos3; i < perm.size(); ++i)
	{
		p.push_back(perm[i]);
	}
	for (size_t i = pos2; i < pos3; ++i)
	{
		p.push_back(perm[i]);
	}
	for (size_t i = pos1; i < pos2; ++i)
	{
		p.push_back(perm[i]);
	}
}


void perturbation(candidate_solution& candidate, std::vector<std::vector<double> > &cities, candidate_solution & best)
{
	double_bridge_move(candidate.vector, best.vector);
	candidate.cost = cost(candidate.vector, cities);
}


void search(candidate_solution & best, std::vector<std::vector<double> > & cities, size_t max_iterations, size_t max_no_improv)
{
	random_permutation(best.vector, cities);
	best.cost = cost(best.vector, cities);
	local_search(best, cities, max_no_improv);
	for (size_t iter = 0; iter < max_iterations; ++iter)
	{
		candidate_solution candidate;
		perturbation(candidate, cities, best);
		local_search(candidate, cities, max_no_improv);
		if (best.cost >= candidate.cost)
		{
			best = candidate;
		}

		std::cout << " > iteration "<< iter + 1 << ", best=" << best.cost << std::endl;
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
	const size_t max_iterations = 100;
	const size_t max_no_improv = 50;
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, max_iterations, max_no_improv);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (size_t i = 0; i < best.vector.size(); ++i)
		std::cout << best.vector[i] << " ";
	std::cout << "}" << std::endl;

	return 0;
}
