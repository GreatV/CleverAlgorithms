#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <cfloat>
#include <map>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

using candidate_solution = struct candidate_solution_st
{
	std::vector<double> vector;
	size_t label = 0;
	double affinity = DBL_MAX;
	double stimulation = 0.0;
	double resources = 0.0;
};

using domain_info = std::map<size_t, std::vector<std::vector<double>>>;


void random_vector(std::vector<double>& vector,
                   const std::vector<std::vector<double>>& min_max)
{
	vector.resize(min_max.size());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		vector[i] = min_max[i][0] + random_double() * (min_max[i][1] - min_max[i][0]);
	}
}

void generate_random_pattern(candidate_solution& pattern, domain_info& domain)
{
	std::vector<size_t> tmp_indexes;
	for (auto& item : domain)
	{
		tmp_indexes.push_back(item.first);
	}
	const auto random_index = static_cast<size_t>(random_double() * (tmp_indexes.size() - 1));
	const size_t class_label = tmp_indexes[random_index];
	pattern.label = class_label;
	random_vector(pattern.vector, domain[class_label]);
}

void create_cell(candidate_solution& cell,
                 const std::vector<double>& vector,
                 const size_t class_label)
{
	cell.vector = vector;
	cell.label = class_label;
}

void initialize_cells(std::vector<candidate_solution>& mem_cells, const domain_info& domain)
{
	for (const auto& item : domain)
	{
		candidate_solution cell;
		std::vector<double> vector;
		std::vector<std::vector<double>> min_max = {{0.0, 1.0}, {0.0, 1.0}};
		random_vector(vector, min_max);
		create_cell(cell, vector, item.first);
		mem_cells.push_back(cell);
	}
}

double distance(const std::vector<double>& x, const std::vector<double>& y)
{
	double sum = 0.0;
	for (size_t i = 0; i < x.size(); ++i)
	{
		sum += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return sqrt(sum);
}

void stimulate(std::vector<candidate_solution>& cells,
               const candidate_solution& pattern)
{
	const std::vector<double> x0 = {0.0, 0.0};
	const std::vector<double> y0 = {1.0, 1.0};
	const auto max_distance = distance(x0, y0);
	for (auto& cell : cells)
	{
		cell.affinity = distance(cell.vector, pattern.vector) / max_distance;
		cell.stimulation = 1.0 - cell.affinity;
	}
}

void get_most_stimulated_cell(candidate_solution& cell,
                              std::vector<candidate_solution>& mem_cells,
                              const candidate_solution& pattern)
{
	stimulate(mem_cells, pattern);
	std::sort(mem_cells.begin(), mem_cells.end(),
	          [](const candidate_solution& a, const candidate_solution& b)
	          {
		          return a.stimulation > b.stimulation;
	          });
	cell = mem_cells[0];
}

void mutate_cell(candidate_solution& cell,
                 const candidate_solution& best_match)
{
	const double range = 1.0 - best_match.stimulation;
	for (double& v : cell.vector)
	{
		const auto min = std::max(v - range / 2.0, 0.0);
		const auto max = std::min(v + range / 2.0, 1.0);
		v = min + random_double() * (max - min);
	}
}

void create_arb_pool(std::vector<candidate_solution>& pool,
                     candidate_solution& pattern,
                     const candidate_solution& best_match,
                     const double clone_rate,
                     const double mutation_rate)
{
	pool.clear();
	candidate_solution tmp_candidate;
	create_cell(tmp_candidate, best_match.vector, best_match.label);
	pool.push_back(tmp_candidate);
	const auto num_clones = static_cast<size_t>(best_match.stimulation * clone_rate * mutation_rate);
	for (size_t i = 0; i < num_clones; ++i)
	{
		candidate_solution cell;
		create_cell(cell, best_match.vector, best_match.label);
		mutate_cell(cell, best_match);
		pool.push_back(cell);
	}
}

double competition_for_resources(std::vector<candidate_solution>& pool,
                                 const double clone_rate,
                                 const double max_resources)
{
	for (auto& cell : pool)
	{
		cell.resources = cell.stimulation * clone_rate;
	}
	std::sort(pool.begin(), pool.end(),
	          [](const candidate_solution& a, const candidate_solution& b)
	          {
		          return a.resources < b.resources;
	          });
	auto total_resources = 0.0;
	for (const auto& cell : pool)
	{
		total_resources += cell.resources;
	}
	while (total_resources > max_resources)
	{
		const auto cell = pool.back();
		total_resources -= cell.resources;
	}

	return total_resources;
}

void refine_arb_pool(candidate_solution& candidate,
                     std::vector<candidate_solution>& pool,
                     const candidate_solution& pattern,
                     const double stimulation_threshold,
                     const double clone_rate,
                     const double max_resources)
{
	double mean_stimulation = 0.0;
	while (mean_stimulation < stimulation_threshold)
	{
		stimulate(pool, pattern);
		std::sort(pool.begin(), pool.end(),
		          [](const candidate_solution& a, const candidate_solution& b)
		          {
			          return a.stimulation > b.stimulation;
		          });
		candidate = pool[0];
		for (const auto& cell : pool)
		{
			mean_stimulation += cell.stimulation;
		}
		mean_stimulation /= pool.size();
		if (candidate.stimulation > mean_stimulation)
		{
			competition_for_resources(pool, clone_rate, max_resources);
			for (auto& i : pool)
			{
				candidate_solution cell;
				create_cell(cell, i.vector, i.label);
				mutate_cell(cell, i);
				i = cell;
				//pool.push_back(cell);
			}
		}
	}
}

void add_candidate_to_memory_pool(
	std::vector<candidate_solution>& mem_cells,
	const candidate_solution& candidate,
	const candidate_solution& best_match)
{
	if (candidate.stimulation > best_match.stimulation)
	{
		mem_cells.push_back(candidate);
	}
}

void classify_pattern(
	candidate_solution& cell,
	std::vector<candidate_solution>& mem_cells,
	const candidate_solution& pattern)
{
	stimulate(mem_cells, pattern);
	std::sort(mem_cells.begin(), mem_cells.end(),
	          [](const candidate_solution& a, const candidate_solution& b)
	          {
		          return a.stimulation > b.stimulation;
	          });
	cell = mem_cells[0];
}

void train_system(std::vector<candidate_solution>& mem_cells,
                  domain_info& domain,
                  const size_t num_patterns,
                  const double clone_rate,
                  const double mutation_rate,
                  const double stimulation_threshold,
                  const double max_resources)
{
	for (size_t i = 0; i < num_patterns; ++i)
	{
		candidate_solution pattern;
		generate_random_pattern(pattern, domain);
		candidate_solution best_match;
		get_most_stimulated_cell(best_match, mem_cells, pattern);
		if (best_match.label != pattern.label)
		{
			candidate_solution candidate;
			create_cell(candidate, pattern.vector, pattern.label);
			mem_cells.push_back(candidate);
		}
		else if (best_match.stimulation < 1.0)
		{
			std::vector<candidate_solution> pool;
			create_arb_pool(pool, pattern, best_match, clone_rate, mutation_rate);
			candidate_solution candidate;
			refine_arb_pool(candidate, pool, pattern, stimulation_threshold, clone_rate, max_resources);
			add_candidate_to_memory_pool(mem_cells, candidate, best_match);
		}
		std::cout << " > iter=" << i + 1 << ", mem_cells=" << mem_cells.size() << std::endl;
	}
}

size_t test_system(std::vector<candidate_solution>& mem_cells,
                   domain_info& domain,
                   const size_t num_trials = 50)
{
	size_t correct = 0;
	for (size_t i = 0; i < num_trials; ++i)
	{
		candidate_solution pattern;
		generate_random_pattern(pattern, domain);
		candidate_solution best;
		classify_pattern(best, mem_cells, pattern);
		if (best.label == pattern.label)
		{
			++correct;
		}
	}
	std::cout << "Finished test with a score of " << correct * 1.0 / num_trials << std::endl;
	return correct;
}

void execute(std::vector<candidate_solution>& mem_cells,
             domain_info& domain,
             const size_t num_patterns,
             const double clone_rate,
             const double mutation_rate,
             const double stimulation_threshold,
             const double max_resources)
{
	mem_cells.clear();
	initialize_cells(mem_cells, domain);
	train_system(mem_cells, domain, num_patterns, clone_rate, mutation_rate, stimulation_threshold, max_resources);
	test_system(mem_cells, domain);
}

int main(int argc, char* argv[])
{
	// problem configuration
	std::vector<std::vector<double>> bounds_0 = {{0.0, 0.4999999}, {0.0, 0.4999999}};
	std::vector<std::vector<double>> bounds_1 = {{0.5, 1.0}, {0.5, 1.0}};
	std::pair<size_t, std::vector<std::vector<double>>> a{0, bounds_0};
	std::pair<size_t, std::vector<std::vector<double>>> b{1, bounds_1};
	domain_info domain;
	domain.insert(a);
	domain.insert(b);
	const size_t num_patterns = 50;
	// algorithm configuration
	const double clone_rate = 10;
	const double mutation_rate = 2.0;
	const double stimulation_threshold = 0.9;
	const double max_resources = 150.0;
	// execute the algorithm
	std::vector<candidate_solution> mem_cells;
	execute(mem_cells, domain, num_patterns, clone_rate, mutation_rate, stimulation_threshold, max_resources);
	return 0;
}
