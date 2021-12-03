#include <random>
#include <iostream>
#include <vector>
#include <cmath>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };


void random_vector(std::vector<double>& x,
                   const std::vector<std::vector<double>>& min_max)
{
	x.clear();
	for (const auto& i : min_max)
	{
		auto tmp = i[0] + (i[1] - i[0]) * random_double();
		x.push_back(tmp);
	}
}

void initialize_weights(std::vector<double>& w, const size_t problem_size)
{
	std::vector<std::vector<double>> min_max;
	for (size_t i = 0; i < problem_size + 1; i++)
	{
		std::vector<double> tmp;
		tmp.push_back(-1.0);
		tmp.push_back(1.0);
		min_max.push_back(tmp);
	}
	random_vector(w, min_max);
}

void update_weights(const size_t num_inputs,
                    std::vector<double>& weights,
                    const std::vector<double>& inputs,
                    const double out_exp,
                    const double out_act,
                    const double l_rate)
{
	for (size_t i = 0; i < num_inputs; ++i)
	{
		weights[i] += l_rate * (out_exp - out_act) * inputs[i];
	}
	weights[num_inputs] += l_rate * (out_exp - out_act);
}

double activate(const std::vector<double>& weights,
                const std::vector<double>& vector)
{
	double sum = 0.0;
	for (size_t i = 0; i < vector.size(); ++i)
	{
		sum += weights[i] * vector[i];
	}
	sum += weights[vector.size()];
	return sum;
}

double transfer(double activation)
{
	return activation >= 0.0 ? 1.0 : 0.0;
}

double get_output(const std::vector<double>& weights,
                  const std::vector<double>& vector)
{
	const double activation = activate(weights, vector);
	return transfer(activation);
}

void train_weights(std::vector<double>& weights,
                   const std::vector<std::vector<double>>& domain,
                   const size_t num_inputs,
                   const size_t iterations,
                   const double l_rate)
{
	for (size_t i = 0; i < iterations; ++i)
	{
		double error = 0.0;
		for (auto& pattern : domain)
		{
			std::vector<double> input(num_inputs);
			for (size_t k = 0; k < num_inputs; ++k)
			{
				input[k] = pattern[k];
			}
			const auto output = get_output(weights, input);
			const auto expected = *(pattern.end() - 1);
			error += abs(output - expected);
			update_weights(num_inputs, weights, input, expected, output, l_rate);
		}
		std::cout << "Epoch: " << i << " Error: " << error << std::endl;
	}
}

size_t test_weights(const std::vector<double>& weights,
                    const std::vector<std::vector<double>>& domain,
                    const size_t num_inputs)
{
	size_t correct = 0;
	for (auto& pattern : domain)
	{
		std::vector<double> input_vector(num_inputs);
		for (size_t k = 0; k < num_inputs; ++k)
		{
			input_vector[k] = pattern[k];
		}
		const auto output = get_output(weights, input_vector);
		if (output - *(pattern.end() - 1) < 1e-6)
		{
			correct += 1;
		}
	}
	std::cout << "Finished test with a score of " << correct / domain.size() << std::endl;
	return correct;
}

void execute(std::vector<double>& weights,
             const std::vector<std::vector<double>>& domain,
             const size_t num_inputs,
             const size_t iterations,
             const double learning_rate)
{
	initialize_weights(weights, num_inputs);
	train_weights(weights, domain, num_inputs, iterations, learning_rate);
	test_weights(weights, domain, num_inputs);
}

int main()
{
	// problem configuration
	const std::vector<std::vector<double>> or_problem = {
		{0, 0, 0},
		{0, 1, 1},
		{1, 0, 1},
		{1, 1, 1}
	};
	const size_t inputs = 2;
	// algorithm configuration
	const size_t iterations = 20;
	const double learning_rate = 0.1;
	// execute the algorithm
	std::vector<double> weights(inputs + 1);
	execute(weights, or_problem, inputs, iterations, learning_rate);
	return 0;
}
