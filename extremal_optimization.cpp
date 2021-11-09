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


using city_info = struct city_st
{
	size_t number = 0;
	double distance = 0.0;
	double fitness = 0.0;
	double prob = 0.0;
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


bool cmp_distance(const city_info& l, const city_info& r)
{
	if (l.distance < r.distance)
	{
		return true;
	}
	return false;
}


void calculate_neighbor_rank(std::vector<city_info>& neighbors,
                             const size_t city_number,
                             const std::vector<std::vector<double>>& cities,
                             const std::vector<size_t>& ignore)
{
	for (size_t i = 0; i < cities.size(); ++i)
	{
		auto& city = cities[i];
		if (i == city_number || std::find(ignore.begin(), ignore.end(), i) != ignore.end())
		{
			continue;
		}
		city_info neighbor;
		neighbor.number = i;
		neighbor.distance = euc_2d(cities[city_number], city);
		neighbors.push_back(neighbor);
	}

	std::sort(neighbors.begin(), neighbors.end(), cmp_distance);
}


void get_edges_for_city(size_t& c1, size_t& c2, const size_t city_number,
                        const std::vector<size_t>& permutation)
{
	for (size_t i = 0; i < permutation.size(); ++i)
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


double calculate_city_fitness(const std::vector<size_t>& permutation,
                              const size_t city_number,
                              const std::vector<std::vector<double>>& cities)
{
	size_t c1, c2;
	get_edges_for_city(c1, c2, city_number, permutation);
	std::vector<city_info> neighbors;
	std::vector<size_t> ignore;
	calculate_neighbor_rank(neighbors, city_number, cities, ignore);
	long long n1 = -1, n2 = -1;
	for (size_t i = 0; i < neighbors.size(); ++i)
	{
		const auto& neighbor = neighbors[i];
		if (neighbor.number == c1)
			n1 = i + 1;
		if (neighbor.number == c2)
			n2 = i + 1;
		if (n1 != -1 && n2 != -1)
			break;
	}

	return 3.0 / static_cast<double>(n1 + n2);
}


bool cmp_fitness(const city_info& l, const city_info& r)
{
	if (l.fitness < r.fitness)
	{
		return true;
	}
	return false;
}

void calculate_city_fitnesses(std::vector<city_info>& city_fitnesses,
                              const std::vector<std::vector<double>>& cities,
                              const std::vector<size_t>& permutation)
{
	city_fitnesses.clear();
	for (size_t i = 0; i < cities.size(); ++i)
	{
		city_info city_fitness;
		city_fitness.number = i;
		city_fitness.fitness = calculate_city_fitness(permutation, i, cities);
		city_fitnesses.push_back(city_fitness);
	}
	std::sort(city_fitnesses.begin(), city_fitnesses.end(), cmp_fitness);
}


double calculate_component_probabilities(std::vector<city_info>& ordered_components,
                                         const double tau = 0.0)
{
	double sum = 0.0;
	for (size_t i = 0; i < ordered_components.size(); ++i)
	{
		auto& component = ordered_components[i];
		component.prob = pow(i + 1.0, -tau);
		sum += component.prob;
	}
	return sum;
}


size_t make_selection(const std::vector<city_info>& components, const double sum_probability)
{
	auto selection = random_();
	for (const auto& component : components)
	{
		selection -= component.prob / sum_probability;
		if (selection <= 0.0)
		{
			return component.number;
		}
	}

	const auto& last = *(components.end() - 1);
	return last.number;
}


size_t probabilistic_selection(std::vector<city_info>& ordered_components,
                               const double tau,
                               const std::vector<size_t>& exclude)
{
	const double sum = calculate_component_probabilities(ordered_components, tau);
	size_t selected_city = make_selection(ordered_components, sum);
	while (std::find(exclude.begin(), exclude.end(), selected_city) != exclude.end())
	{
		selected_city = make_selection(ordered_components, sum);
	}
	return selected_city;
}


void vary_permutation(std::vector<size_t>& perm,
                      const std::vector<size_t>& permutation,
                      const size_t selected,
                      const size_t new_value,
                      const size_t long_edge
)
{
	perm.clear();
	perm = permutation;
	const size_t c1 = std::find(perm.begin(), perm.end(), selected) - perm.begin();
	const size_t c2 = std::find(perm.begin(), perm.end(), new_value) - perm.begin();
	size_t p1, p2;
	if (c1 < c2)
	{
		p1 = c1;
		p2 = c2;
	}
	else
	{
		p1 = c2;
		p2 = c1;
	}
	const auto right = c1 == perm.size() - 1 ? 0 : c1 + 1;
	if (perm[right] == long_edge)
	{
		for (size_t i = p1 + 1; i < (p2 - p1 - 1) / 2; ++i)
		{
			const auto tmp = perm[i];
			perm[i] = perm[p2 - i + p1 + 1];
			perm[p2 - i + p1 + 1] = tmp;
		}
	}
	else
	{
		for (size_t i = p1; i < (p2 - p1) / 2; ++i)
		{
			const auto tmp = perm[i];
			perm[i] = perm[p2 - i + p1];
			perm[p2 - i + p1] = tmp;
		}
	}
}


size_t get_long_edge(const std::vector<size_t>& edges,
                     const std::vector<city_info>& neighbor_distances)
{
	city_info n1, n2;
	for (const auto& neighbor_distance : neighbor_distances)
	{
		if (neighbor_distance.number == edges[0])
		{
			n1 = neighbor_distance;
		}
	}

	for (const auto& neighbor_distance : neighbor_distances)
	{
		if (neighbor_distance.number == edges[1])
		{
			n2 = neighbor_distance;
		}
	}
	return n1.distance > n2.distance ? n1.number : n2.number;
}


void create_new_perm(std::vector<size_t>& permutation,
                     const std::vector<std::vector<double>>& cities,
                     const double tau,
                     const std::vector<size_t>& perm)
{
	std::vector<city_info> city_fitnesses;
	calculate_city_fitnesses(city_fitnesses, cities, perm);
	std::vector<size_t> exclude;
	for (size_t i = 0; i < city_fitnesses.size() / 2; ++i)
	{
		const auto& tmp = city_fitnesses[i];
		city_fitnesses[i] = *(city_fitnesses.end() - 1 - i);
		*(city_fitnesses.end() - 1 - i) = tmp;
	}
	const auto selected_city = probabilistic_selection(city_fitnesses, tau, exclude);
	std::vector<size_t> edges(2);
	get_edges_for_city(edges[0], edges[1], selected_city, perm);
	std::vector<city_info> neighbors;
	std::vector<size_t> ignore;
	calculate_neighbor_rank(neighbors, selected_city, cities, ignore);
	const auto new_neighbor = probabilistic_selection(neighbors, tau, edges);
	const auto long_edge = get_long_edge(edges, neighbors);
	vary_permutation(permutation, perm, selected_city, new_neighbor, long_edge);
}


void search(candidate_solution& best,
            const std::vector<std::vector<double>>& cities,
            const size_t max_iterations,
            const double tau)
{
	candidate_solution current;
	random_permutation(current.vector, cities);
	current.cost = cost(current.vector, cities);
	best = current;
	for (size_t iter = 0; iter < max_iterations; ++iter)
	{
		candidate_solution candidate;
		create_new_perm(candidate.vector, cities, tau, current.vector);
		candidate.cost = cost(candidate.vector, cities);
		current = candidate;
		if (candidate.cost < best.cost)
		{
			best = candidate;
		}
		std::cout << " > iter " << iter + 1 << ", curr = " << current.cost << ", best = "
			<< best.cost << std::endl;
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
	const size_t max_iterations = 250;
	const double tau = 1.8;
	// execute the algorithm
	candidate_solution best;
	search(best, berlin52, max_iterations, tau);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (unsigned int i : best.vector)
		std::cout << i << " ";
	std::cout << "}" << std::endl;

	return 0;
}
