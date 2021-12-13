#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::vector<double> vector;
	double cost = 0;
};


double objective_function(const std::vector<double>& vector)
{
	double sum = 0.0;
	for (const double val : vector)
	{
		sum += val * val;
	}

	return sum;
}


void random_vector(std::vector<double>& arr, const std::vector<std::vector<double>>& minmax)
{
	arr.clear();
	for (const auto& item : minmax)
	{
		arr.push_back(item[0] + (item[1] - item[0]) * random_());
	}
}


void de_rand_1_bin(candidate_solution& sample, const candidate_solution& p0,
                   const candidate_solution& p1, const candidate_solution& p2,
                   const candidate_solution& p3, const double f, const double cr,
                   const std::vector<std::vector<double>>& search_space)
{
	sample.vector.clear();
	sample.vector.resize(p0.vector.size());
	const size_t cut = static_cast<size_t>((sample.vector.size() - 2) * random_()) + 1;
	for (size_t i = 0; i < sample.vector.size(); ++i)
	{
		sample.vector[i] = p0.vector[i];
		if (i == cut || random_() < cr)
		{
			auto v = p3.vector[i] + f * (p1.vector[i] - p2.vector[i]);
			if (v < search_space[i][0])
				v = search_space[i][0];
			if (v > search_space[i][1])
				v = search_space[i][1];
			sample.vector[i] = v;
		}
	}
}


void select_parents(size_t& p1, size_t& p2, size_t& p3,
                    const std::vector<candidate_solution>& pop, const size_t current)
{
	p1 = static_cast<size_t>((pop.size() - 1) * random_());
	p2 = static_cast<size_t>((pop.size() - 1) * random_());
	p3 = static_cast<size_t>((pop.size() - 1) * random_());
	while (p1 == current)
	{
		p1 = static_cast<size_t>((pop.size() - 1) * random_());
	}

	while (p2 == current || p2 == p1)
	{
		p2 = static_cast<size_t>((pop.size() - 1) * random_());
	}

	while (p3 == current || p3 == p2 || p3 == p1)
	{
		p3 = static_cast<size_t>((pop.size() - 1) * random_());
	}
}


void create_children(std::vector<candidate_solution>& children,
                     const std::vector<candidate_solution>& pop,
                     const std::vector<std::vector<double>>& minmax,
                     const double f, const double cr)
{
	children.clear();
	for (size_t i = 0; i < pop.size(); ++i)
	{
		auto pop0 = pop[i];
		size_t p1, p2, p3;
		select_parents(p1, p2, p3, pop, i);
		candidate_solution child;
		de_rand_1_bin(child, pop0, pop[p1], pop[p2], pop[p3], f, cr, minmax);
		children.push_back(child);
	}
}


void select_population(std::vector<candidate_solution>& pop,
                       const std::vector<candidate_solution>& parents,
                       const std::vector<candidate_solution>& children)
{
	std::vector<candidate_solution> tmp_pop;
	tmp_pop.resize(parents.size());
	for (size_t i = 0; i < parents.size(); ++i)
	{
		tmp_pop[i] = children[i].cost <= parents[i].cost ? children[i] : parents[i];
	}

	pop = tmp_pop;
}


bool cmp(const candidate_solution& c_l, const candidate_solution& c_r)
{
	if (c_l.cost < c_r.cost)
	{
		return true;
	}

	return false;
}


void search(candidate_solution& best, const size_t max_gens,
            const std::vector<std::vector<double>>& search_space,
            const size_t pop_size, const double f, const double cr)
{
	std::vector<candidate_solution> pop;
	pop.resize(pop_size);
	for (auto& item : pop)
	{
		random_vector(item.vector, search_space);
		item.cost = objective_function(item.vector);
	}

	std::sort(pop.begin(), pop.end(), cmp);
	best = pop[0];

	for (size_t gen = 0; gen < max_gens; ++gen)
	{
		std::vector<candidate_solution> children;
		create_children(children, pop, search_space, f, cr);
		for (auto& item : children)
		{
			item.cost = objective_function(item.vector);
		}

		select_population(pop, pop, children);
		std::sort(pop.begin(), pop.end(), cmp);
		if (pop[0].cost < best.cost)
		{
			best = pop[0];
		}
		std::cout << " > gen " << gen << ", best: " << best.cost << std::endl;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 3;
	std::vector<std::vector<double>> search_space;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> space{-5, 5};
		search_space.push_back(space);
	}
	// algorithm configuration
	const size_t max_gens = 200;
	const size_t pop_size = 10 * problem_size;
	const double weight_f = 0.8;
	const double cross_f = 0.9;
	// execute the algorithm
	candidate_solution best;
	search(best, max_gens, search_space, pop_size, weight_f, cross_f);

	std::cout << "Done. Solution: f = " << best.cost << ", s = ";
	for (auto& vec : best.vector)
		std::cout << vec << " ";
	std::cout << std::endl;

	return 0;
}
