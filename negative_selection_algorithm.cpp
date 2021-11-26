#include <vector>
#include <random>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

using candidate_solution = struct candidate_solution_st
{
	std::vector<double> vector;
	std::string bit_string;
	double fitness = DBL_MAX;
	double affinity = 0.0;
};


void random_vector(std::vector<double> & vector,
const std::vector<std::vector<double>> & min_max)
{
    vector.resize(min_max.size());
    for (size_t i = 0; i < vector.size(); ++i)
    {
        vector[i] = min_max[i][0] + random_double() * (min_max[i][1] - min_max[i][0]);
    }
}

double euclidean_distance(const std::vector<double> & x,
const std::vector<double> & y)
{
    double sum = 0.0;
    for (size_t i = 0; i < x.size(); ++i)
    {
        sum += (x[i] - y[i]) * (x[i] - y[i]);
    }
    return sqrt(sum);
}

bool contains(const std::vector<double> & x,
const std::vector<std::vector<double>> & space)
{
    for(size_t i = 0; i < space.size(); ++i)
    {
        if(x[i] < space[i][0] || x[i] > space[i][1])
        {
            return false;
        }
    }
    return true;
}

bool matches(const std::vector<double> & x,
const std::vector<candidate_solution> & dataset,
const double min_distance)
{
    for(const auto pattern : dataset)
    {
        if(euclidean_distance(x, pattern.vector) < min_distance)
        {
            return true;
        }
    }
    return false;
}

void generate_detectors(std::vector<candidate_solution> & detectors,
const size_t max_detectors,
const std::vector<std::vector<double>> & search_space,
const std::vector<candidate_solution> & self_dataset,
const double min_distance)
{
    detectors.clear();
    while(detectors.size() < max_detectors)
    {
        candidate_solution detector;
        random_vector(detector.vector, search_space);
        if(!matches(detector.vector, self_dataset, min_distance) && !matches(detector.vector, detectors, 0.0))
        {
        {
            detectors.push_back(detector);
        }
        detectors.push_back(detector);
    }
}
