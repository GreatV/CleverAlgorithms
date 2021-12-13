#include <vector>
#include <random>
#include <cmath>
#include <iostream>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

using candidate_solution = struct candidate_solution_st
{
	std::vector<double> vector;
};


void random_vector(std::vector<double>& vector,
                   const std::vector<std::vector<double>>& min_max)
{
	vector.resize(min_max.size());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		vector[i] = min_max[i][0] + random_double() * (min_max[i][1] - min_max[i][0]);
	}
}

double euclidean_distance(const std::vector<double>& x,
                          const std::vector<double>& y)
{
	double sum = 0.0;
	for (size_t i = 0; i < x.size(); ++i)
	{
		sum += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return sqrt(sum);
}

bool contains(const std::vector<double>& x,
              const std::vector<std::vector<double>>& space)
{
	for (size_t i = 0; i < space.size(); ++i)
	{
		if (x[i] < space[i][0] || x[i] > space[i][1])
		{
			return false;
		}
	}
	return true;
}

bool matches(const std::vector<double>& x,
             const std::vector<candidate_solution>& dataset,
             const double min_distance)
{
	for (const auto & pattern : dataset)
	{
		if (euclidean_distance(x, pattern.vector) < min_distance)
		{
			return true;
		}
	}
	return false;
}

void generate_detectors(std::vector<candidate_solution>& detectors,
                        const size_t max_detectors,
                        const std::vector<std::vector<double>>& search_space,
                        const std::vector<candidate_solution>& self_dataset,
                        const double min_distance)
{
	detectors.clear();
	while (detectors.size() < max_detectors)
	{
		candidate_solution detector;
		random_vector(detector.vector, search_space);
		if (!matches(detector.vector, self_dataset, min_distance) && !matches(detector.vector, detectors, 0.0))
		{
			{
				detectors.push_back(detector);
			}
			detectors.push_back(detector);
		}
	}
}

void generate_self_dataset(std::vector<candidate_solution>& self_dataset,
                           const size_t num_records,
                           const std::vector<std::vector<double>>& self_space,
                           const std::vector<std::vector<double>>& search_space)
{
	self_dataset.clear();
	while (self_dataset.size() < num_records)
	{
		candidate_solution pattern;
		random_vector(pattern.vector, search_space);
		if (matches(pattern.vector, self_dataset, 0.0))
		{
			continue;
		}
		if (!contains(pattern.vector, self_space))
		{
			self_dataset.push_back(pattern);
		}
	}
}

size_t apply_detectors(const std::vector<candidate_solution>& detectors,
                       const std::vector<std::vector<double>>& bounds,
                       const std::vector<candidate_solution>& self_dataset,
                       const double min_distance,
                       const size_t trials = 50)
{
	size_t correct = 0;
	for (size_t i = 0; i < trials; ++i)
	{
		candidate_solution input;
		random_vector(input.vector, bounds);
		const auto actual = matches(input.vector, detectors, min_distance) ? 'N' : 'S';
		const auto expected = matches(input.vector, self_dataset, min_distance) ? 'S' : 'N';
		if (actual == expected)
		{
			correct += 1;
		}

		std::cout << i + 1 << "/" << trials << " Actual: " << actual << " Expected: " << expected << std::endl;
	}
	std::cout << "Done. Result: " << correct * 1.0 / trials << std::endl;
	return correct;
}

void execute(std::vector<candidate_solution>& detectors,
             const std::vector<std::vector<double>>& bounds,
             const std::vector<std::vector<double>>& self_space,
             const size_t max_detect,
             const size_t max_self,
             const double min_distance)
{
	std::vector<candidate_solution> self_dataset;
	generate_self_dataset(self_dataset, max_self, self_space, bounds);
	std::cout << "Done: prepared " << self_dataset.size() << " self patterns." << std::endl;
	generate_detectors(detectors, max_detect, bounds, self_dataset, min_distance);
	std::cout << "Done: prepared " << detectors.size() << " detectors." << std::endl;
	apply_detectors(detectors, bounds, self_dataset, min_distance);
}

int main()
{
	// problem configuration
	const size_t problem_size = 2;
	std::vector<std::vector<double>> bounds(problem_size);
	for (auto& bound : bounds)
	{
		bound.resize(2);
		bound[0] = 0.0;
		bound[1] = 1.0;
	}
	std::vector<std::vector<double>> self_space(problem_size);
	for (auto& bound : self_space)
	{
		bound.resize(2);
		bound[0] = 0.5;
		bound[1] = 1.0;
	}
	const size_t max_self = 150;
	// algorithm configuration
	const size_t max_detectors = 300;
	const double min_distance = 0.05;
	// execute the algorithm
	std::vector<candidate_solution> detectors;
	execute(detectors, bounds, self_space, max_detectors, max_self, min_distance);
	return 0;
}
