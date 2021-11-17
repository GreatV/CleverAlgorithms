#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>


using candidate_info = struct candidate_info_t
{
	std::vector<double> vector;
	double cost = 0.0;
};


double random(const double min, const double max)
{
	const double range = max - min;
	const double div = RAND_MAX / range;
	return min + (rand() / div);
}


double objective_function(const std::vector<double>& x)
{
	double result = 0.0;
	for (const double i : x)
	{
		result += i * i;
	}
	return result;
}


double random_variable(const double min, const double max)
{
	return random(min, max);
}


double random_gaussian(const double mean = 0.0, const double std_dev = 1.0)
{
	double u1 = 2.0 * random(0.0, 1.0) - 1.0;
	double u2 = 2.0 * random(0.0, 1.0) - 1.0;
	double w = u1 * u1 + u2 * u2;

	while (w >= 1.0)
	{
		u1 = 2.0 * random(0.0, 1.0) - 1.0;
		u2 = 2.0 * random(0.0, 1.0) - 1.0;
		w = u1 * u1 + u2 * u2;
	}

	w = sqrt((-2.0 * log(w)) / w);
	return mean + (u2 * w) * std_dev;
}


void generate_sample(std::vector<double>& x,
                     const std::vector<std::vector<double>>& search_space,
                     const std::vector<double>& means, const std::vector<double>& std_devs)
{
	x.clear();
	x.resize(search_space.size());
	for (size_t i = 0; i < x.size(); i++)
	{
		x[i] = random_gaussian(means[i], std_devs[i]);
		if (x[i] < search_space[i][0])
		{
			x[i] = search_space[i][0];
		}
		if (x[i] > search_space[i][1])
		{
			x[i] = search_space[i][1];
		}
	}
}


double mean_attribute(const std::vector<candidate_info>& samples, const size_t attribute)
{
	double sum = 0.0;
	for (const auto& sample : samples)
	{
		sum += sample.vector[attribute];
	}
	return sum / samples.size();
}


double std_dev_attribute(const std::vector<candidate_info>& samples, const double mean, const size_t attribute)
{
	double sum = 0.0;
	for (const auto& sample : samples)
	{
		sum += (sample.vector[attribute] - mean) * (sample.vector[attribute] - mean);
	}
	return sqrt(sum / samples.size());
}


void update_distribution(const std::vector<candidate_info>& samples, const double alpha,
                         std::vector<double>& means, std::vector<double>& std_devs)
{
	for (size_t i = 0; i < means.size(); ++i)
	{
		means[i] = alpha * means[i] + (1.0 - alpha) * mean_attribute(samples, i);
		std_devs[i] = alpha * std_devs[i] + (1.0 - alpha) * std_dev_attribute(samples, means[i], i);
	}
}


bool cmp_cost(const candidate_info& a, const candidate_info& b)
{
	return a.cost < b.cost;
}


void search(candidate_info& best, const std::vector<std::vector<double>>& search_space,
            const size_t max_iterations, const size_t num_samples,
            const size_t num_updates, const double learning_rate)
{
	std::vector<double> means(search_space.size());
	std::vector<double> std_devs(search_space.size());
	for (size_t i = 0; i < means.size(); ++i)
	{
		means[i] = random_variable(search_space[i][0], search_space[i][1]);
		std_devs[i] = search_space[i][1] - search_space[i][0];
	}
	for (size_t iter = 0; iter < max_iterations; ++iter)
	{
		std::vector<candidate_info> samples(num_samples);
		for (auto& sample : samples)
		{
			generate_sample(sample.vector, search_space, means, std_devs);
			sample.cost = objective_function(sample.vector);
		}
		std::sort(samples.begin(), samples.end(), cmp_cost);
		if (samples[0].cost < best.cost || iter == 0)
		{
			best = samples[0];
		}
		std::vector<candidate_info> selected(num_updates);
		for (size_t i = 0; i < selected.size(); ++i)
		{
			selected[i] = samples[i];
		}
		update_distribution(selected, learning_rate, means, std_devs);
		std::cout << "Iteration: " << iter << " Best: " << best.cost << std::endl;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t problem_size = 3;
	std::vector<std::vector<double>> search_space(problem_size);
	for (auto& bound : search_space)
	{
		bound.resize(2);
		bound[0] = -5.0;
		bound[1] = 5.0;
	}
	// algorithm configuration
	const size_t max_iterations = 100;
	const size_t num_samples = 50;
	const size_t num_updates = 5;
	const double learning_rate = 0.7;
	// execute the algorithm
	candidate_info best;
	search(best, search_space, max_iterations, num_samples, num_updates, learning_rate);
	std::cout << "done! Solution: f = " << best.cost << " s = ";
	for (const auto& x : best.vector)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
