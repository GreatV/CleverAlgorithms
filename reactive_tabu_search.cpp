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

using entry_info = struct entry_info_t
{
	std::vector<std::pair<size_t, size_t>> edgelist;
	std::vector<size_t> edge;
	size_t iter = 0;
	size_t visits = 0;
	bool enable = true;
};

double euc_2d(std::vector<double> & c1, std::vector<double> &c2)
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

double cost(std::vector<size_t> & perm, std::vector<std::vector<double>> & cities)
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

void random_permutation(std::vector<size_t> & perm, std::vector<std::vector<double>>& cities)
{
	perm.clear();
	perm.resize(cities.size());

	for (size_t i = 0; i < cities.size(); ++i)
	{
		perm[i] = i;
	}

	for (size_t i = 0; i < cities.size(); ++i)
	{
		const size_t r = (size_t)((perm.size() - 1 - i) * random_()) + i;
		const size_t tmp = perm[r];
		perm[r] = perm[i];
		perm[i] = tmp;
	}
}

void stochastic_two_opt(std::vector<size_t> & perm, std::vector<std::vector<size_t>> & edges,
	std::vector<size_t> & parent)
{
	perm.clear();
	edges.clear();
	perm.resize(parent.size());
	perm.assign(parent.begin(), parent.end());
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

	std::vector<size_t> edge0 = { parent[c1_m_1], parent[c1] };
	std::vector<size_t> edge1 = { parent[c2_m_1], parent[c2] };
	edges.push_back(edge0);
	edges.push_back(edge1);
}

bool is_tabu(std::vector<size_t> & edge, std::vector<entry_info> & tabu_list,
	const size_t iter, const double prohib_period)
{
	for (size_t i = 0; i < tabu_list.size(); ++i)
	{
		auto & entry = tabu_list[i];
		if (entry.edge == edge)
		{
			if (entry.iter >= iter - prohib_period)
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

void make_tabu(entry_info & entry, std::vector<entry_info> & tabu_list,
	std::vector<size_t> & edge, const size_t iter)
{
	for (size_t i = 0; i < tabu_list.size(); ++i)
	{
		auto & item = tabu_list[i];
		if (item.edge == edge)
		{
			item.iter = iter;
			entry.edge = item.edge;
			entry.iter = item.iter;
			return;
		}
	}

	entry.edge = edge;
	entry.iter = iter;
	tabu_list.push_back(entry);
}

void to_edge_list(std::vector<std::pair<size_t, size_t>>& list, std::vector<size_t> & perm)
{
	list.clear();
	for (size_t i = 0; i < perm.size(); ++i)
	{
		auto c1 = perm[i];
		auto c2 = i == perm.size() - 1 ? perm[0] : perm[i + 1];
		if (c1 > c2)
		{
			const auto tmp = c1;
			c1 = c2;
			c2 = tmp;
		}
		std::pair<size_t, size_t> item(c1, c2);
		list.push_back(item);
	}
}

bool equivalent(std::vector<std::pair<size_t, size_t>> & el1,
	std::vector<std::pair<size_t, size_t>> & el2)
{
	for (size_t i = 0; i < el1.size(); ++i)
	{
		if (std::find(el2.begin(), el2.end(), el1[i]) == el2.end())
		{
			return false;
		}
	}

	return true;
}

void generate_candidate(candidate_solution & candidate, std::vector<std::vector<size_t>> & edges,
	candidate_solution & best,
	std::vector<std::vector<double>> & cities)
{
	stochastic_two_opt(candidate.vector, edges, best.vector);
	candidate.cost = cost(candidate.vector, cities);
}

void get_candidate_entry(entry_info & entry, std::vector<entry_info> & visited_list,
	std::vector<size_t> & permutation)
{
	std::vector<std::pair<size_t, size_t>> edge_list;
	to_edge_list(edge_list, permutation);

	for (size_t i = 0; i < visited_list.size(); ++i)
	{
		auto& item = visited_list[i];
		if (equivalent(edge_list, item.edgelist))
		{
			entry = item;
			entry.enable = true;
			return;
		}
	}

	entry.enable = false;
}

void store_permutation(entry_info & entry, std::vector<entry_info> & visited_list,
	std::vector<size_t> & permutation, const size_t iteration)
{
	to_edge_list(entry.edgelist, permutation);
	entry.iter = iteration;
	entry.visits = 1;
	visited_list.push_back(entry);
}

using candidate_info = struct candidate_info_t
{
	candidate_solution candidate;
	std::vector<std::vector<size_t>> edges;
};

void sort_neighborhood(std::vector<candidate_info> & tabu,
	std::vector<candidate_info> & admissable,
	std::vector<candidate_info> & candidates,
	std::vector<entry_info>  & tabu_list,
	const double prohib_period, const size_t iteration)
{
	tabu.clear();
	admissable.clear();

	for (size_t i = 0; i < candidates.size(); ++i)
	{
		auto & a = candidates[i];
		if (is_tabu(a.edges[0], tabu_list, iteration, prohib_period) ||
			is_tabu(a.edges[1], tabu_list, iteration, prohib_period))
		{
			tabu.push_back(a);
		}
		else
		{
			admissable.push_back(a);
		}
	}
}

bool cmp(candidate_info & info_l, candidate_info & info_r)
{
	if (info_l.candidate.cost < info_r.candidate.cost)
	{
		return true;
	}

	return false;
}

void search(candidate_solution & best,
	std::vector<std::vector<double>> & cities,
	const size_t max_cand,
	const size_t max_iter,
	const double increase,
	const double decrease)
{
	candidate_solution current;
	random_permutation(current.vector, cities);
	current.cost = cost(current.vector, cities);
	best = current;
	std::vector<entry_info> tabu_list;
	double prohib_period = 1;
	std::vector<entry_info> visited_list;
	double avg_size = 1;
	int last_change = 0;
	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		entry_info candidate_entry;
		get_candidate_entry(candidate_entry, visited_list, current.vector);
		if (candidate_entry.enable)
		{
			const size_t repetition_interval = iter - candidate_entry.iter;
			candidate_entry.iter = iter;
			candidate_entry.visits += 1;

			if (repetition_interval < 2 * (cities.size() - 1))
			{
				avg_size = 0.1 * (iter - candidate_entry.iter) + 0.9 * avg_size;
				prohib_period = ((double)prohib_period * increase);
				last_change = iter;
			}
			else
			{
				entry_info tmp_entry;
				store_permutation(tmp_entry, visited_list, current.vector, iter);
			}
		}

		if (iter - last_change > avg_size)
		{
			prohib_period = std::max(prohib_period * decrease, 1.0);
			last_change = iter;
		}

		std::vector<candidate_info> candidates;
		for (size_t i = 0; i < max_cand; ++i)
		{
			candidate_solution cand;
			std::vector<std::vector<size_t>> edges;
			generate_candidate(cand, edges, current, cities);
			candidate_info item;
			item.candidate = cand;
			item.edges = edges;
			candidates.push_back(item);
		}

		std::sort(candidates.begin(), candidates.end(), cmp);

		std::vector<candidate_info> tabu;
		std::vector<candidate_info> admis;
		sort_neighborhood(tabu, admis, candidates, tabu_list, prohib_period, iter);
		if (admis.size() < 2)
		{
			prohib_period = cities.size() - 2;
			last_change = iter;
		}

		std::vector<std::vector<size_t>> best_move_edges;

		if (admis.empty())
		{
			current = tabu[0].candidate;
			best_move_edges = tabu[0].edges;
		}
		else
		{
			current = admis[0].candidate;
			best_move_edges = admis[0].edges;
		}

		if (!tabu.empty())
		{
			auto tf = tabu[0].candidate;
			if (tf.cost < best.cost && tf.cost < current.cost)
			{
				current = tabu[0].candidate;
				best_move_edges = tabu[0].edges;
			}
		}

		for (size_t i = 0; i < best_move_edges.size(); ++i)
		{
			auto & edge = best_move_edges[i];
			entry_info tmp_entry;
			make_tabu(tmp_entry, tabu_list, edge, iter);
		}

		if (candidates[0].candidate.cost < best.cost)
		{
			best = candidates[0].candidate;
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
	const size_t max_candidates = 50;
	const double increase = 1.3;
	const double decrease = 0.9;
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, max_candidates, max_iter, increase, decrease);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (auto & i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
