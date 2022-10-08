#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <cfloat>
#include <deque>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using candidate_solution = struct candidate_solution_st
{
	std::string bit_string;
	double fitness = DBL_MIN;
};


using node_info = struct node_info_st
{
	size_t num = 0;
	int count = 0;
	std::vector<size_t> out;
	std::vector<size_t> in;
};


double onemax(const std::string& bit_string)
{
	double sum = 0.0;
	for (auto& item : bit_string)
	{
		if (item == '1')
		{
			sum++;
		}
	}
	return sum;
}


void random_bit_string(std::string& bit_string, const size_t size)
{
	bit_string.clear();
	for (size_t i = 0; i < size; ++i)
	{
		bit_string.push_back(random_() < 0.5 ? '1' : '0');
	}
}


bool path_exists(const size_t i, const size_t j,
                 const std::vector<node_info>& graph)
{
	std::deque<size_t> visited, stack;
	stack.push_back(i);
	while (!stack.empty())
	{
		if (std::find(stack.begin(), stack.end(), j) != stack.end())
		{
			return true;
		}
		auto k = stack[0];
		stack.pop_front();
		if (std::find(visited.begin(), visited.end(), k) != visited.end())
		{
			continue;
		}
		visited.push_back(k);
		for (auto& m : graph[k].out)
		{
			if (std::find(visited.begin(), visited.end(), m) == visited.end())
			{
				stack.push_front(m);
			}
		}
	}

	return false;
}


bool can_add_edge(const size_t i, const size_t j, std::vector<node_info>& graph)
{
	const bool flag0 = std::find(graph[i].out.begin(), graph[i].out.end(), j) != graph[i].out.end();
	const bool flag1 = path_exists(j, i, graph);
	return (!flag0 && !flag1);
}


void get_viable_parents(std::vector<size_t>& viable, const size_t node, std::vector<node_info>& graph)
{
	viable.clear();
	for (size_t i = 0; i < graph.size(); ++i)
	{
		if (node != i && can_add_edge(node, i, graph))
		{
			viable.push_back(i);
		}
	}
}


void compute_count_for_edges(std::vector<size_t>& counts,
                             const std::vector<candidate_solution>& pop,
                             const std::vector<size_t>& indexes)
{
	counts.clear();
	counts.resize(static_cast<size_t>(pow(2, indexes.size())));
	for (auto& count : counts)
	{
		count = 0;
	}
	for (auto& p : pop)
	{
		size_t index = 0;
		for (size_t i = 0; i < indexes.size(); ++i)
		{
			const auto v = *(indexes.end() - 1 - static_cast<int>(i));
			const auto j = indexes.size() - 1 - i;
			index += (p.bit_string[v] == '1' ? 1 : 0) * static_cast<size_t>(pow(2, j));
		}
		counts[index] += 1;
	}
}


double fact(double v)
{
	return v <= 1 ? 1 : v * fact(v - 1);
}


double k2equation(const size_t node,
                  const std::vector<size_t>& candidates,
                  const std::vector<candidate_solution>& pop)
{
	std::vector<size_t> counts;
	std::vector<size_t> tmp;
	tmp.push_back(node);
	for (unsigned int candidate : candidates)
	{
		tmp.push_back(candidate);
	}
	compute_count_for_edges(counts, pop, tmp);
	double total = 0.0;
	for (size_t i = 0; i < counts.size() / 2; ++i)
	{
		const auto a1 = counts[i * 2];
		const auto a2 = counts[i * 2 + 1];
		const auto rs = 1.0 / fact((a1 + a2) + 1) * fact(a1) * fact(a2);
		if (i == 0)
		{
			total = rs;
		}
		else
		{
			total *= rs;
		}
	}
	return total;
}


void compute_gains(std::vector<double>& gains,
                   const node_info& node, std::vector<node_info>& graph,
                   const std::vector<candidate_solution>& pop,
                   const size_t max = 2)
{
	gains.clear();
	gains.resize(graph.size());

	for (auto& gain : gains)
	{
		gain = -1.0;
	}

	std::vector<size_t> viable;
	get_viable_parents(viable, node.num, graph);

	for (size_t i = 0; i < gains.size(); ++i)
	{
		if (graph[i].in.size() < max && std::find(viable.begin(), viable.end(), i) != viable.end())
		{
			auto tmp = node.in;
			tmp.push_back(i);
			gains[i] = k2equation(node.num, tmp, pop);
		}
	}
}


void construct_network(std::vector<node_info>& graph,
                       const std::vector<candidate_solution>& pop,
                       const size_t prob_size,
                       const size_t max_edges)
{
	graph.clear();
	graph.resize(prob_size);
	for (size_t i = 0; i < graph.size(); ++i)
	{
		graph[i].num = i;
	}
	std::vector<std::vector<double>> gains(prob_size);
	for (size_t t = 0; t < max_edges; ++t)
	{
		size_t from, to;
		double max = -1.0;
		for (size_t i = 0; i < graph.size(); ++i)
		{
			auto& node = graph[i];
			compute_gains(gains[i], node, graph, pop);
			for (size_t j = 0; j < gains[i].size(); ++j)
			{
				const auto& v = gains[i][j];
				if (v > max)
				{
					from = i;
					to = j;
					max = v;
				}
			}
		}
		if (max < 0.0)
			break;
		graph[from].out.push_back(to);
		graph[to].in.push_back(from);
	}
}


void topological_ordering(std::vector<node_info>& ordered, std::vector<node_info>& graph)
{
	for (auto& n : graph)
	{
		n.count = static_cast<int>(n.in.size());
	}
	std::deque<node_info> stack;
	for (auto& n : graph)
	{
		if (n.count == 0)
		{
			stack.push_back(n);
		}
	}
	ordered.clear();
	while (ordered.size() < graph.size())
	{
		auto current = stack[0];
		stack.pop_front();
		for (const auto& edge : current.out)
		{
			for (auto& n : graph)
			{
				if (n.num == edge)
				{
					auto& node = n;
					node.count -= 1;
					if (node.count <= 0)
					{
						stack.push_back(node);
					}
					break;
				}
			}
		}
		ordered.push_back(current);
	}
}


double marginal_probability(const size_t i, const std::vector<candidate_solution>& pop)
{
	double s = 0.0;
	for (auto& j : pop)
	{
		s += (j.bit_string[i] - '0') * 1.0;
	}
	s /= pop.size();
	return s;
}


double calculate_probability(const node_info& node, const std::string& bit_string,
                             std::vector<node_info>& graph, const std::vector<candidate_solution>& pop)
{
	if (node.in.empty())
	{
		return marginal_probability(node.num, pop);
	}
	std::vector<size_t> counts;
	std::vector<size_t> tmp;
	tmp.push_back(node.num);
	for (unsigned int i : node.in)
	{
		tmp.push_back(i);
	}
	compute_count_for_edges(counts, pop, tmp);
	double index = 0.0;
	for (size_t i = 0; i < node.in.size(); ++i)
	{
		const auto j = node.in.size() - 1 - i;
		const auto v = *(node.in.end() - 1 - static_cast<int>(i));
		index += (bit_string[v] == '1' ? 1 : 0) * pow(2, j);
	}
	const auto i1 = static_cast<size_t>(index + (1 * pow(2, node.in.size())));
	const auto i2 = static_cast<size_t>(index + (0 * pow(2, node.in.size())));
	const auto a1 = counts[i1];
	const auto a2 = counts[i2];
	return a1 * 1.0 / (a1 + a2);
}


void probabilistic_logic_sample(std::string& bit_string,
                                std::vector<node_info>& graph,
                                const std::vector<candidate_solution>& pop)
{
	bit_string.clear();
	bit_string.resize(graph.size());
	for (auto& node : graph)
	{
		const auto prob = calculate_probability(node, bit_string, graph, pop);
		bit_string[node.num] = random_() < prob ? '1' : '0';
	}
}


void sample_from_network(
	std::vector<candidate_solution>& samples,
	const std::vector<candidate_solution>& pop,
	std::vector<node_info>& graph,
	const size_t num_samples)
{
	std::vector<node_info> ordered;
	topological_ordering(ordered, graph);
	samples.clear();
	samples.resize(num_samples);
	for (auto& sample : samples)
	{
		probabilistic_logic_sample(sample.bit_string, ordered, pop);
	}
}


bool cmp_fitness(const candidate_solution& x, const candidate_solution& y)
{
	if (x.fitness > y.fitness)
	{
		return true;
	}
	return false;
}


void search(candidate_solution& best,
            const size_t num_bits,
            const size_t max_iter,
            const size_t pop_size,
            const size_t select_size,
            const size_t num_children)
{
	std::vector<candidate_solution> pop(pop_size);
	for (auto& p : pop)
	{
		random_bit_string(p.bit_string, num_bits);
		p.fitness = onemax(p.bit_string);
	}
	std::sort(pop.begin(), pop.end(), cmp_fitness);
	best = pop[0];
	for (size_t it = 0; it < max_iter; ++it)
	{
		std::vector<candidate_solution> selected(select_size);
		for (size_t i = 0; i < select_size; ++i)
		{
			selected[i] = pop[i];
		}
		std::vector<node_info> network;
		construct_network(network, selected, num_bits, 3 * selected.size());
		size_t arcs = 0;
		for (auto& i : network)
		{
			arcs += i.out.size();
		}
		std::vector<candidate_solution> children;
		sample_from_network(children, selected, network, num_children);
		for (auto& c : children)
		{
			c.fitness = onemax(c.bit_string);
			std::cout << " >> sample, f = " << c.fitness << " " << c.bit_string << std::endl;
		}
		for (size_t i = pop_size - select_size; i < pop_size; ++i)
		{
			pop[i] = children[i - pop_size + select_size];
		}
		std::sort(pop.begin(), pop.end(), cmp_fitness);
		if (pop[0].fitness > best.fitness)
		{
			best = pop[0];
		}
		std::cout << " > it = " << it + 1 << ", arcs = " << arcs
			<< ", f = "
			<< best.fitness << ", b = "
			<< best.bit_string << std::endl;

		if (static_cast<size_t>(best.fitness) == num_bits)
		{
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t num_bits = 20;
	// algorithm configuration
	const size_t max_iter = 10;
	const size_t pop_size = 50;
	const size_t select_size = 15;
	const size_t num_children = 25;
	// execute the algorithm
	candidate_solution best;
	search(best, num_bits, max_iter, pop_size, select_size, num_children);

	std::cout << "Done! Solution: f = " << best.fitness;
	std::cout << ", b = " << best.bit_string << std::endl;

	return 0;
}
