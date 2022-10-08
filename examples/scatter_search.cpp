#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::vector<double> vector;
	double cost = 0.0;
	double dist = 0.0;
	bool is_new = false;

	bool operator <(const candidate_solution_t& candidate) const
	{
		return vector < candidate.vector;
	}

	bool operator ==(const candidate_solution_t& candidate) const
	{
		return vector == candidate.vector;
	}
};


double objective_function(std::vector<double>& vector)
{
	double sum = 0.0;
	for (double& item : vector)
	{
		sum += item * item;
	}

	return sum;
}


double rand_in_bounds(const double min, const double max)
{
	return min + (max - min) * random_();
}


void random_vector(std::vector<double>& arr, std::vector<std::vector<double>>& minmax)
{
	arr.clear();
	arr.resize(minmax.size());
	for (size_t i = 0; i < minmax.size(); ++i)
	{
		arr[i] = rand_in_bounds(minmax[i][0], minmax[i][1]);
	}
}


void take_step(std::vector<double>& position, std::vector<std::vector<double>>& minmax,
               std::vector<double>& current, const double step_size)
{
	position.clear();
	position.resize(current.size());
	for (size_t i = 0; i < current.size(); ++i)
	{
		const double min = std::max(minmax[i][0], current[i] - step_size);
		const double max = std::min(minmax[i][1], current[i] - step_size);
		position[i] = rand_in_bounds(min, max);
	}
}


void local_search(candidate_solution& best, std::vector<std::vector<double>>& bounds, const size_t max_no_improv,
                  const double step_size)
{
	size_t count = 0;
	while (count < max_no_improv)
	{
		candidate_solution candidate;
		take_step(candidate.vector, bounds, best.vector, step_size);
		candidate.cost = objective_function(candidate.vector);
		count = candidate.cost < best.cost ? 0 : count + 1;
		if (candidate.cost < best.cost)
		{
			best = candidate;
		}
	}
}

bool is_any_element_equal(std::vector<candidate_solution>& set, std::vector<double>& vec)
{
	if (set.empty())
	{
		return false;
	}

	for (auto& i : set)
	{
		if (i.vector.size() == vec.size() &&
			std::equal(i.vector.begin(), i.vector.end(), vec.begin()))
		{
			return true;
		}
	}
	return false;
}

void construct_initial_set(std::vector<candidate_solution>& diverse_set, std::vector<std::vector<double>>& bounds,
                           const size_t set_size, const size_t max_no_improv, const double step_size)
{
	diverse_set.clear();
	while (diverse_set.size() < set_size)
	{
		candidate_solution cand;
		random_vector(cand.vector, bounds);
		cand.cost = objective_function(cand.vector);
		local_search(cand, bounds, max_no_improv, step_size);
		if (!is_any_element_equal(diverse_set, cand.vector))
		{
			diverse_set.push_back(cand);
		}
	}
}


double euclidean_distance(std::vector<double>& c1, std::vector<double>& c2)
{
	double sum = 0.0;
	for (size_t i = 0; i < c1.size(); ++i)
	{
		sum += (c1[i] - c2[i]) * (c1[i] - c2[i]);
	}

	return sqrt(sum);
}


double distance(std::vector<double>& v, std::vector<candidate_solution>& set)
{
	double s = 0.0;
	for (auto& i : set)
	{
		s += euclidean_distance(v, i.vector);
	}
	return s;
}


bool cmp_cost(candidate_solution& x, candidate_solution& y)
{
	if (x.cost < y.cost)
	{
		return true;
	}
	return false;
}


bool cmp_dist(candidate_solution& x, candidate_solution& y)
{
	if (x.dist < y.dist)
	{
		return true;
	}
	return false;
}


void diversify(std::vector<candidate_solution>& ref_set, std::vector<candidate_solution>& diverse_set,
               const size_t num_elite, const size_t ref_set_size)
{
	std::sort(diverse_set.begin(), diverse_set.end(), cmp_cost);
	ref_set.clear();
	ref_set.resize(num_elite);
	for (size_t i = 0; i < num_elite; ++i)
	{
		ref_set[i] = diverse_set[i];
	}
	std::vector<candidate_solution> remainder;

	std::vector<candidate_solution> sorted_ref_set(ref_set);
	std::sort(sorted_ref_set.begin(), sorted_ref_set.end());
	std::vector<candidate_solution> sorted_diverse_set(diverse_set);
	std::sort(sorted_diverse_set.begin(), sorted_diverse_set.end());

	std::set_difference(sorted_diverse_set.begin(), sorted_diverse_set.end(),
	                    sorted_ref_set.begin(), sorted_ref_set.end(),
	                    std::inserter(remainder, remainder.begin()));
	for (auto& i : remainder)
	{
		candidate_solution c = i;
		i.dist = distance(c.vector, ref_set);
	}
	std::sort(remainder.begin(), remainder.end(), cmp_dist);

	for (size_t i = 0; i < ref_set_size - num_elite; ++i)
	{
		ref_set.push_back(remainder[i]);
	}
}


bool is_include(std::vector<std::pair<candidate_solution, candidate_solution>>& subsets,
                std::pair<candidate_solution, candidate_solution>& subset)
{
	for (auto& i : subsets)
	{
		if (i.first == subset.first && i.second == subset.second)
		{
			return true;
		}
	}
	return false;
}


void select_subsets(std::vector<std::pair<candidate_solution, candidate_solution>>& subsets,
                    std::vector<candidate_solution>& ref_set)
{
	std::vector<candidate_solution> additions;
	for (auto& i : ref_set)
	{
		if (i.is_new)
		{
			additions.push_back(i);
		}
	}

	std::vector<candidate_solution> remainder;

	std::vector<candidate_solution> sorted_ref_set(ref_set);
	std::sort(sorted_ref_set.begin(), sorted_ref_set.end());
	std::vector<candidate_solution> sorted_additions(additions);
	std::sort(sorted_additions.begin(), sorted_additions.end());

	std::set_difference(sorted_ref_set.begin(), sorted_ref_set.end(),
	                    sorted_additions.begin(), sorted_additions.end(),
	                    std::inserter(remainder, remainder.begin()));

	if (remainder.empty())
	{
		remainder = additions;
	}

	subsets.clear();
	for (auto& a : additions)
	{
		for (auto& r : remainder)
		{
			std::pair<candidate_solution, candidate_solution> subset_ra(r, a);
			if (a.vector != r.vector && !is_include(subsets, subset_ra))
			{
				std::pair<candidate_solution, candidate_solution> subset_ar(a, r);
				subsets.push_back(subset_ar);
			}
		}
	}
}


void recombine(std::vector<candidate_solution>& children,
               std::pair<candidate_solution, candidate_solution>& subset,
               std::vector<std::vector<double>>& minmax)
{
	candidate_solution a = subset.first;
	candidate_solution b = subset.second;

	std::vector<double> d;
	for (size_t i = 0; i < a.vector.size(); ++i)
	{
		d.push_back((b.vector[i] - a.vector[i]) / 2.0);
	}
	children.clear();

	std::vector<candidate_solution> tmp = {a, b};
	for (auto& p : tmp)
	{
		const double direction = random_() < 0.5 ? 1.0 : -1.0;
		const double r = random_();
		candidate_solution child;
		child.vector.resize(minmax.size());
		for (size_t j = 0; j < child.vector.size(); ++j)
		{
			child.vector[j] = p.vector[j] + (direction * r * d[j]);
			if (child.vector[j] < minmax[j][0])
			{
				child.vector[j] = minmax[j][0];
			}

			if (child.vector[j] > minmax[j][1])
			{
				child.vector[j] = minmax[j][1];
			}
		}

		child.cost = objective_function(child.vector);
		children.push_back(child);
	}
}


bool explore_subsets(std::vector<std::vector<double>>& bounds, std::vector<candidate_solution>& ref_set,
                     const size_t max_no_improv, const double step_size)
{
	bool was_change = false;
	std::vector<std::pair<candidate_solution, candidate_solution>> subsets;
	select_subsets(subsets, ref_set);
	for (auto& i : ref_set)
	{
		i.is_new = false;
	}

	for (auto& subset : subsets)
	{
		std::vector<candidate_solution> candidates;
		recombine(candidates, subset, bounds);

		std::vector<candidate_solution> improved;
		improved.resize(candidates.size());
		for (size_t j = 0; j < improved.size(); ++j)
		{
			improved[j] = candidates[j];
			local_search(improved[j], bounds, max_no_improv, step_size);
		}
		for (auto& j : improved)
		{
			if (!is_any_element_equal(ref_set, j.vector))
			{
				j.is_new = true;
				std::sort(ref_set.begin(), ref_set.end(), cmp_cost);
				const auto ref_last = *(ref_set.end() - 1);
				if (j.cost < ref_last.cost)
				{
					ref_set.pop_back();
					ref_set.push_back(j);
					std::cout << " > added, cost=" << j.cost << std::endl;
					was_change = true;
				}
			}
		}
	}
	return was_change;
}


void search(candidate_solution& best, std::vector<std::vector<double>>& bounds,
            const size_t max_iter, const size_t ref_set_size,
            const size_t div_set_size, const size_t max_no_improv,
            const double step_size, const size_t max_elite)
{
	std::vector<candidate_solution> diverse_set;
	construct_initial_set(diverse_set, bounds, div_set_size, max_no_improv, step_size);
	std::vector<candidate_solution> ref_set;
	diversify(ref_set, diverse_set, max_elite, ref_set_size);
	best = ref_set[0];

	for (auto& item : ref_set)
	{
		item.is_new = true;
	}

	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		const bool was_change = explore_subsets(bounds, ref_set, max_no_improv, step_size);
		std::sort(ref_set.begin(), ref_set.end(), cmp_cost);

		if (ref_set[0].cost < best.cost)
		{
			best = ref_set[0];
		}
		std::cout << " > iter=" << iter + 1 << " best=" << best.cost << std::endl;

		if (!was_change)
			break;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 3;
	std::vector<std::vector<double>> bounds;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> bound = {-5.0, 5.0};
		bounds.push_back(bound);
	}
	// algorithm configuration
	const size_t max_iter = 100;
	const double step_size = (bounds[0][1] - bounds[0][0]) * 0.005;
	const size_t max_no_improv = 30;
	const size_t ref_set_size = 10;
	const size_t diverse_set_size = 20;
	const size_t no_elite = 5;
	// execute the algorithm
	candidate_solution best;
	search(best, bounds, max_iter, ref_set_size, diverse_set_size,
	       max_no_improv, step_size, no_elite);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (auto& item : best.vector)
		std::cout << item << " ";
	std::cout << "}" << std::endl;

	return 0;
}
