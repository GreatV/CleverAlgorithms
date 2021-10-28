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
	if (c1.size() != c2.size())
	{
		return 0.0;
	}

	double sum = 0.0;
	for (size_t i = 0; i < c1.size(); ++i)
	{
		sum += (c1[i] - c2[i]) * (c1[i] - c2[i]);
	}

	return sqrt(sum);
}


double cost(std::vector<size_t>& perm, std::vector<std::vector<double>>& cities)
{
	double distance = 0.0;
	for (size_t i = 0; i < perm.size(); ++i)
	{
		const size_t c1 = perm[i];
		const size_t c2 = i == perm.size() - 1 ? perm[0] : perm[i + 1];

		distance += euc_2d(cities[c1], cities[c2]);
	}

	return distance;
}


void random_permutation(std::vector<size_t>& perm, std::vector<std::vector<double>>& cities)
{
	perm.clear();
	perm.resize(cities.size());

	for (size_t i = 0; i < cities.size(); ++i)
	{
		perm[i] = i;
	}

	for (size_t i = 0; i < cities.size(); ++i)
	{
		const size_t r = static_cast<size_t>((perm.size() - 1 - i) * random_()) + i;
		const size_t tmp = perm[r];
		perm[r] = perm[i];
		perm[i] = tmp;
	}
}

void stochastic_two_opt(std::vector<size_t>& perm, std::vector<std::vector<size_t>>& edges,
                        std::vector<size_t>& parent)
{
	perm.clear();
	edges.clear();
	perm.resize(parent.size());
	perm.assign(parent.begin(), parent.end());
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
		const size_t tmp = perm[c1];
		perm[c1] = perm[c2 - (i - c1)];
		perm[c2 - (i - c1)] = tmp;
	}

	const size_t c1_m_1 = c1 == 0 ? perm.size() - 1 : c1 - 1;
	const size_t c2_m_1 = c2 == 0 ? perm.size() - 1 : c2 - 1;

	const std::vector<size_t> edge0 = {parent[c1_m_1], parent[c1]};
	const std::vector<size_t> edge1 = {parent[c2_m_1], parent[c2]};
	edges.push_back(edge0);
	edges.push_back(edge1);
}


bool is_tabu(std::vector<size_t>& permutation, std::vector<std::vector<size_t>>& tabu_list)
{
	for (size_t i = 0; i < permutation.size(); ++i)
	{
		const size_t c1 = permutation[i];
		const size_t c2 = (i == permutation.size() - 1) ? permutation[0] : permutation[i + 1];
		for (size_t j = 0; j < tabu_list.size(); ++j)
		{
			std::vector<size_t> forbidden_edge;
			forbidden_edge.resize(tabu_list[j].size());
			forbidden_edge = tabu_list[j];
			std::vector<size_t> tmp = {c1, c2};
			if (forbidden_edge == tmp)
			{
				return true;
			}
		}
	}
	return false;
}


void generate_candidate(candidate_solution& candidate, std::vector<std::vector<size_t>>& edges,
                        candidate_solution& best,
                        std::vector<std::vector<size_t>>& tabu_list,
                        std::vector<std::vector<double>>& cities)
{
	std::vector<size_t> perm;
	edges.clear();
	stochastic_two_opt(perm, edges, best.vector);
	while (is_tabu(perm, tabu_list))
	{
		stochastic_two_opt(perm, edges, best.vector);
	}
	candidate.vector = perm;
	candidate.cost = cost(candidate.vector, cities);
}


using candidate_info = struct candidate_info_t
{
	candidate_solution candidate;
	std::vector<std::vector<size_t>> edges;
};


bool cmp(candidate_info& info_l, candidate_info& info_r)
{
	if (info_l.candidate.cost < info_r.candidate.cost)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best,
            std::vector<std::vector<double>>& cities,
            const size_t tabu_list_size,
            const size_t candidate_list_size, const size_t max_iter)
{
	candidate_solution current;
	random_permutation(current.vector, cities);
	current.cost = cost(current.vector, cities);
	best = current;
	std::vector<std::vector<size_t>> tabu_list;
	tabu_list.clear();
	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		std::vector<candidate_info> candidates(candidate_list_size);
		for (size_t i = 0; i < candidate_list_size; ++i)
		{
			generate_candidate(candidates[i].candidate, candidates[i].edges,
			                   current, tabu_list, cities);
		}
		std::sort(candidates.begin(), candidates.end(), cmp);
		const candidate_solution best_candidate = candidates[0].candidate;
		std::vector<std::vector<size_t>> best_candidate_edges = candidates[0].edges;
		if (best_candidate.cost < current.cost)
		{
			current = best_candidate;
			if (best_candidate.cost < best.cost)
			{
				best = best_candidate;
			}
			for (auto& edge : best_candidate_edges)
			{
				tabu_list.push_back(edge);
			}
			while (tabu_list.size() > tabu_list_size)
			{
				tabu_list.pop_back();
			}
		}
		std::cout << " > iteration " << iter + 1 << ", best=" << best.cost << std::endl;
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
	const size_t max_iter = 100;
	const size_t tabu_list_size = 15;
	const size_t max_candidates = 50;
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, tabu_list_size, max_candidates, max_iter);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (auto& i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
