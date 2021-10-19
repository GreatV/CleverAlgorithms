#include <iostream>
#include <numeric>
#include <random>
#include <vector>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random = [&]() {return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::vector<double> vector;
	double cost = 0.0;
};


double objective_function(std::vector<double>& vector)
{
	return std::inner_product(vector.begin(), vector.end(), vector.begin(), 0.0);
}


double rand_in_bounds(double min, double max)
{
	return min + (max - min) * random();
}


void random_vector(std::vector<double>& rand_vec, std::vector<std::vector<double> >& minmax)
{
	if (minmax.empty())
	{
		return;
	}
	rand_vec.resize(minmax.size());
	for (size_t i = 0; i < minmax.size(); ++i)
	{
		rand_vec[i] = rand_in_bounds(minmax[i][0], minmax[i][1]);
	}
}


void take_step(std::vector<double> & position, std::vector<std::vector<double> > & minmax, std::vector<double> & current, double step_size)
{
	position.resize(current.size());
	for (size_t i = 0; i < current.size(); ++i)
	{
		double min = std::max(minmax[i][0], current[i] - step_size);
		double max = std::min(minmax[i][1], current[i] + step_size);
		position[i] = rand_in_bounds(min, max);
	}
}


double large_step_size(size_t iter, double step_size, double s_factor, double l_factor, size_t iter_mult)
{
	if (iter > 0 && (iter % iter_mult == 0))
	{
		return step_size * l_factor;
	}
	return step_size * s_factor;
}


void take_steps(candidate_solution & step, candidate_solution & big_step, std::vector<std::vector<double> > & bounds, std::vector<double> & current, double step_size, double big_step_size)
{
	take_step(step.vector, bounds, current, step_size);
	step.cost = objective_function(step.vector);
	take_step(big_step.vector, bounds, current, big_step_size);
	big_step.cost = objective_function(big_step.vector);
}


void search(candidate_solution & current, size_t max_iter, std::vector<std::vector<double> > & bounds, double init_factor, double s_factor, double l_factor, size_t iter_mult, size_t max_no_impr)
{
	double step_size = (bounds[0][1] - bounds[0][0]) * init_factor;
	size_t count = 0;
	random_vector(current.vector, bounds);
	current.cost = objective_function(current.vector);

	for (size_t iter = 0; iter < max_iter; ++iter)
	{
		double big_step_size = large_step_size(iter, step_size, s_factor, l_factor, iter_mult);
		candidate_solution step;
		candidate_solution big_step;
		take_steps(step, big_step, bounds, current.vector, step_size, big_step_size);
		if (step.cost <= current.cost || big_step.cost <= current.cost)
		{
			if (big_step.cost <= step.cost)
			{
				step_size = big_step_size;
				current = big_step;
			}
			else
			{
				current = step;
			}
			count = 0;
		}
		else
		{
			count += 1;
			if (count >= max_no_impr)
			{
				count = 0;
				step_size = (step_size / s_factor);
			}
		}
		std::cout << "> iteration " << iter + 1 << ", best = " << current.cost << std::endl;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 2;
	std::vector<std::vector<double> > bounds;
	for (size_t i = 0; i < problem_size; ++i)
	{
		std::vector<double> bound = { -5.0, 5.0 };
		bounds.push_back(bound);
	}
	// algorithm configuration
	const size_t max_iter = 1000;
	const double init_factor = 0.05;
	const double s_factor = 1.3;
	const double l_factor = 3.0;
	const size_t iter_mult = 10;
	const size_t max_no_impr = 30;
	// execute the algorithm
	candidate_solution best;
	search(best, max_iter, bounds, init_factor, s_factor, l_factor, iter_mult, max_no_impr);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v={ ";
	for (size_t i = 0; i < best.vector.size(); ++i)
	{
		std::cout << best.vector[i] << " ";
	}
	std::cout << "}" << std::endl;

	return 0;
}
