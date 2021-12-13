#include <vector>
#include <random>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>

using candidate_info = struct candidate_info_t
{
	std::vector<double> vector;
	double fitness = DBL_MAX;
	double cost = DBL_MAX;
	double inter = DBL_MAX;
	double sum_nutrients = 0.0;
};

std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

double objective_function(const std::vector<double>& x)
{
	return x[0] * x[0] + x[1] * x[1];
}

void random_vector(std::vector<double>& x,
                   const std::vector<std::vector<double>>& min_max)
{
	x.resize(min_max.size());
	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] = min_max[i][0] + random_double() * (min_max[i][1] - min_max[i][0]);
	}
}

void generate_random_direction(std::vector<double>& x,
                               const size_t problem_size)
{
	std::vector<std::vector<double>> bounds(problem_size);
	for (auto& bound : bounds)
	{
		bound.resize(2);
		bound[0] = -1.0;
		bound[1] = 1.0;
	}
	random_vector(x, bounds);
}

double compute_cell_interaction(const candidate_info& cell,
                                const std::vector<candidate_info>& cells,
                                const double d, const double w)
{
	double sum = 0.0;
	for (auto& other : cells)
	{
		double diff = 0.0;
		for (size_t i = 0; i < cell.vector.size(); ++i)
		{
			diff += (cell.vector[i] - other.vector[i]) * (cell.vector[i] - other.vector[i]);
		}
		sum += d * std::exp(w * diff);
	}

	return sum;
}

double attract_repel(const candidate_info& cell,
                     const std::vector<candidate_info>& cells,
                     const double d_attr,
                     const double w_attr,
                     const double h_rep,
                     const double w_rep)
{
	const auto attract = compute_cell_interaction(cell, cells, -d_attr, -w_attr);
	const auto repel = compute_cell_interaction(cell, cells, h_rep, -w_rep);
	return attract + repel;
}

void evaluate(candidate_info& cell,
              const std::vector<candidate_info>& cells,
              const double d_attr,
              const double w_attr,
              const double h_rep,
              const double w_rep)
{
	cell.cost = objective_function(cell.vector);
	cell.inter = attract_repel(cell, cells, d_attr, w_attr, h_rep, w_rep);
	cell.fitness = cell.cost + cell.inter;
}

void tumble_cell(std::vector<double>& x,
                 const std::vector<std::vector<double>>& search_space,
                 const candidate_info& cell,
                 const double step_size)
{
	std::vector<double> step;
	generate_random_direction(step, search_space.size());
	x.resize(search_space.size());
	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] = cell.vector[i] + step_size * step[i];
		if (x[i] < search_space[i][0])
		{
			x[i] = search_space[i][0];
		}
		else if (x[i] > search_space[i][1])
		{
			x[i] = search_space[i][1];
		}
	}
}

void chemotaxis(candidate_info& best,
                std::vector<candidate_info>& cells,
                const std::vector<std::vector<double>>& search_space,
                const size_t chem_steps,
                const size_t swim_length,
                const double step_size,
                const double d_attr,
                const double w_attr,
                const double h_rep,
                const double w_rep)
{
	for (size_t j = 0; j < chem_steps; ++j)
	{
		std::vector<candidate_info> moved_cells;
		for (size_t i = 0; i < cells.size(); ++i)
		{
			auto& cell = cells[i];
			double sum_nutrients = 0.0;
			evaluate(cell, cells, d_attr, w_attr, h_rep, w_rep);
			if (cell.cost < best.cost)
			{
				best = cell;
			}
			sum_nutrients += cell.fitness;
			for (size_t m = 0; m < swim_length; ++m)
			{
				candidate_info new_cell;
				tumble_cell(new_cell.vector, search_space, cell, step_size);
				evaluate(new_cell, cells, d_attr, w_attr, h_rep, w_rep);
				if (best.cost > cell.cost)
				{
					best = cell;
				}
				if (new_cell.fitness > cell.fitness)
				{
					cell = new_cell;
				}
				sum_nutrients += cell.fitness;
			}
			cell.sum_nutrients = sum_nutrients;
			moved_cells.push_back(cell);
		}
		std::cout << " >> chemo = " << j << " , f = "
			<< best.fitness << " cost = " << best.cost << std::endl;
		cells = moved_cells;
	}
}

void search(candidate_info& best,
            const std::vector<std::vector<double>>& search_space,
            const size_t pop_size,
            const size_t elim_disp_steps,
            const size_t repro_steps,
            const size_t chem_steps,
            const size_t swim_length,
            const double step_size,
            const double d_attr,
            const double w_attr,
            const double h_rep,
            const double w_rep,
            const double p_eliminate)
{
	std::vector<candidate_info> cells(pop_size);
	for (auto& cell : cells)
	{
		random_vector(cell.vector, search_space);
	}

	for (size_t l = 0; l < elim_disp_steps; ++l)
	{
		for (size_t k = 0; k < repro_steps; ++k)
		{
			candidate_info c_best;
			chemotaxis(c_best, cells, search_space, chem_steps, swim_length, step_size, d_attr, w_attr, h_rep, w_rep);
			if (l == 0 || c_best.cost < best.cost)
			{
				best = c_best;
			}
			std::cout << "> best fitness=" << best.fitness << ", cost=" << best.cost << std::endl;
			std::sort(cells.begin(), cells.end(), [](const candidate_info& a, const candidate_info& b)
			{
				return a.sum_nutrients < b.sum_nutrients;
			});

			for (size_t i = pop_size / 2; i < cells.size(); ++i)
			{
				cells[i] = cells[i - pop_size / 2];
			}

			for (auto& cell : cells)
			{
				if (random_double() <= p_eliminate)
				{
					random_vector(cell.vector, search_space);
				}
			}
		}
	}
}

int main()
{
	// problem configuration
	const size_t problem_size = 2;
	std::vector<std::vector<double>> search_space(problem_size);
	for (size_t i = 0; i < problem_size; ++i)
	{
		search_space[i].push_back(-5);
		search_space[i].push_back(5);
	}

	// algorithm configuration
	const size_t pop_size = 50;
	const double step_size = 0.1; // Ci
	const size_t elim_disp_steps = 1; // Ned
	const size_t repro_steps = 4; // Nre
	const size_t chem_steps = 70; // Nc
	const size_t swim_length = 4; // Ns
	const double p_eliminate = 0.25; // Ped
	const double d_attr = 0.1;
	const double w_attr = 0.1;
	const double h_rep = d_attr;
	const double w_rep = 10;
	// execute the algorithm
	candidate_info best;
	search(best, search_space, pop_size, elim_disp_steps, repro_steps, chem_steps, swim_length, step_size, d_attr,
	       w_attr, h_rep, w_rep, p_eliminate);
	std::cout << " >> Done. Solution: c = " << best.cost << " v = ";
	for (const auto& v : best.vector)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	return 0;
}
