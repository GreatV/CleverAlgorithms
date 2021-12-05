#include <random>
#include <iostream>
#include <vector>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_double = []() { return distribution(generator); };

using neuron_info = struct neuron_info_st
{
	double output = 0.0;
	std::vector<double> weights;
	double activation = 0.0;
	double delta = 0.0;
	std::vector<double> derivatives;
	std::vector<double> last_delta;
};

void random_vector(std::vector<double> & vector, const std::vector<std::vector<double>> & min_max)
{
	vector.resize(min_max.size());
	for (size_t i = 0; i < min_max.size(); ++i)
	{
		vector[i] = (min_max[i][0] + (min_max[i][1] - min_max[i][0]) * random_double());
	}
}

void initialize_weights(std::vector<double> & vector, const size_t num_weights)
{
	std::vector<std::vector<double>> min_max;
	for (size_t i = 0; i < num_weights; ++i)
	{
		std::vector<double> bound;
		bound.push_back(-random_double());
		bound.push_back(random_double());
		min_max.push_back(bound);
	}
	random_vector(vector, min_max);
}

double activate(const std::vector<double> & weights, const std::vector<double> & vector)
{
	double sum = weights.back() * 1.0;
	for (size_t i = 0; i < vector.size(); ++i)
	{
		sum += weights[i] * vector[i];
	}
	return sum;
}

double transfer(const double activation)
{
	return 1.0 / (1.0 + std::exp(-activation));
}

double transfer_derivative(const double output)
{
	return output * (1.0 - output);
}

double forward_propagate(std::vector<std::vector<neuron_info>> & net, const std::vector<double> & vector)
{
	for (size_t i = 0; i < net.size(); ++i)
	{
		std::vector<double> tmp_vector;
		if (i != 0)
		{
			for (size_t k = 0; k < net[i - 1].size(); ++k)
			{
				tmp_vector.push_back(net[i - 1][k].output);
			}
		}
		auto input = i == 0 ? vector : tmp_vector;
		auto & layer = net[i];
		for (auto & neuron : layer)
		{
			neuron.activation = activate(neuron.weights, input);
			neuron.output = transfer(neuron.activation);
		}
	}
	return net.back()[0].output;
}

void backward_propagate_error(std::vector<std::vector<neuron_info>> & network, const double expected_output)
{
	for (size_t n = 0; n < network.size(); ++n)
	{
		auto index = network.size() - 1 - n;
		if (index == network.size() - 1)
		{
			// assume one node in output layer
			auto & neuron = network[index][0];
			auto error = expected_output - neuron.output;
			neuron.delta = error * transfer_derivative(neuron.output);
		}
		else
		{
			for (size_t k = 0; k < network[index].size(); ++k)
			{
				auto & neuron = network[index][k];
				double sum = 0.0;
				// only sum errors weighted by connection to the current k'th neuron
				for (auto & next_neuron : network[index + 1])
				{
					sum += (next_neuron.weights[k] * next_neuron.delta);
				}
				neuron.delta = sum * transfer_derivative(neuron.output);
			}
		}
	}
}

void calculate_error_derivatives_for_weights(std::vector<std::vector<neuron_info>> & net, const std::vector<double> & vector)
{
	for (size_t i = 0; i < net.size(); ++i)
	{
		auto & layer = net[i];
		std::vector<double> tmp_vector;
		if (i != 0)
		{
			for (size_t k = 0; k < net[i - 1].size(); ++k)
			{
				tmp_vector.push_back(net[i - 1][k].output);
			}
		}
		auto input = i == 0 ? vector : tmp_vector;
		for (auto & neuron : layer)
		{
			for (size_t j = 0; j < input.size(); ++j)
			{
				auto signal = input[j];
				neuron.derivatives[j] += neuron.delta * signal;
			}
			neuron.derivatives.back() += neuron.delta * 1.0;
		}
	}
}

void update_weights(std::vector<std::vector<neuron_info>> & net, const double learning_rate, const double momentum = 0.8)
{
	for (auto & layer : net)
	{
		for (auto & neuron : layer)
		{
			for (size_t j = 0; j < neuron.weights.size(); ++j)
			{
				auto delta = learning_rate * neuron.derivatives[j] + momentum * neuron.last_delta[j];
				neuron.weights[j] += delta;
				neuron.last_delta[j] = delta;
				neuron.derivatives[j] = 0.0;
			}
		}
	}
}

void train_network(std::vector<std::vector<neuron_info>> & network, std::vector<std::vector<int>> & domain, const size_t num_inputs, const size_t iterations, const double learning_rate)
{
	size_t correct = 0;
	for (size_t i = 0; i < iterations; ++i)
	{
		for (auto & pattern : domain)
		{
			std::vector<double> vector;
			for (size_t k = 0; k < num_inputs; ++k)
			{
				vector.push_back(pattern[k]);
			}
			auto expected = pattern.back();
			auto output = forward_propagate(network, vector);
			if (output > 0.5)
			{
				correct++;
			}
			backward_propagate_error(network, expected);
			calculate_error_derivatives_for_weights(network, vector);
		}
		update_weights(network, learning_rate);
		if ((i + 1) % 100 == 0)
		{
			std::cout << " > epoch = " << i + 1 << ", Correct = " << double(correct / (100.0 * domain.size())) << std::endl;
			correct = 0;
		}
	}
}

size_t test_network(std::vector<std::vector<neuron_info>> & network, std::vector<std::vector<int>> & domain, const size_t num_inputs)
{
	size_t correct = 0;
	for (auto & pattern : domain)
	{
		std::vector<double> input_vector;
		for (size_t k = 0; k < num_inputs; ++k)
		{
			input_vector.push_back(pattern[k]);
		}
		auto output = forward_propagate(network, input_vector);
		if (size_t(output) == pattern.back())
		{
			correct++;
		}
	}
	std::cout << "Finished test with a score of " << double(correct / (double(domain.size()))) << std::endl;
	return correct;
}

void create_neuron(neuron_info & neuron, const size_t num_inputs)
{
	initialize_weights(neuron.weights, num_inputs);
	neuron.last_delta.resize(num_inputs + 1);
	for (size_t i = 0; i < num_inputs + 1; ++i)
	{
		neuron.last_delta[i] = 0.0;
	}
	neuron.derivatives.resize(num_inputs + 1);
	for (size_t i = 0; i < num_inputs + 1; ++i)
	{
		neuron.derivatives[i] = 0.0;
	}
}

void execute(std::vector<std::vector<neuron_info>> & network, std::vector<std::vector<int>> & domain, const size_t num_inputs, const size_t iterations, const size_t num_nodes, const double learning_rate)
{
	network.clear();
	std::vector<neuron_info> tmp_nodes;
	for (size_t i = 0; i < num_nodes; ++i)
	{
		neuron_info neuron;
		create_neuron(neuron, num_inputs);
		tmp_nodes.push_back(neuron);
	}
	network.push_back(tmp_nodes);
	std::vector<neuron_info> tmp_bias;
	neuron_info bias;
	create_neuron(bias, network.back().size());
	tmp_bias.push_back(bias);
	network.push_back(tmp_bias);
	std::cout << "Topology: " << num_inputs << " ";
	for (auto & layer : network)
	{
		std::cout << layer.size() << " ";
	}
	std::cout << std::endl;
	train_network(network, domain, num_inputs, iterations, learning_rate);
	test_network(network, domain, num_inputs);
}

int main()
{
	// problem configuration
	std::vector<std::vector<int>> xor_domain{
		{0, 0, 0},
		{ 0, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 0 }
	};
	const size_t inputs = 2;
	// algorithm configuration
	const double learning_rate = 0.3;
	const size_t num_hidden_nodes = 4;
	const size_t iterations = 2000;
	// execute the algorithm
	std::vector<std::vector<neuron_info>> network;
	execute(network, xor_domain, inputs, iterations, num_hidden_nodes, learning_rate);
	return 0;
}
