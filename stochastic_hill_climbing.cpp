#include <iostream>
#include <random>
#include <vector>
#include <string>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random = []() {return distribution(generator); };


using candidate_solution = struct candidate_solution_t
{
	std::string vector;
	double cost = 0.0;
};


double onemax(std::string & vector)
{
	double sum = 0.0;
	for (char i : vector)
	{
		sum += (i == '1' ? 1 : 0);
	}
	
	return sum;
}


void random_bitstring(std::string & vector,  const size_t num_bits)
{
	vector.clear();
	for (size_t i = 0; i < num_bits; ++i)
	{
		vector.push_back(random() < 0.5 ? '1' : '0');
	}
}


void random_neighbor(std::string& mutant, std::string & bitstring)
{
	mutant = bitstring;
	const auto pos = static_cast<size_t>((bitstring.size() - 1) * random());
	mutant[pos] = mutant[pos] == '1' ? '0' : '1';
}


void search(candidate_solution & candidate, const size_t max_iterations, const size_t num_bits)
{
	random_bitstring(candidate.vector, num_bits);
	candidate.cost = onemax(candidate.vector);
	for (size_t iter = 0; iter < max_iterations; ++iter)
	{
		candidate_solution neighbor;
		random_neighbor(neighbor.vector, candidate.vector);
		neighbor.cost = onemax(neighbor.vector);
		if (neighbor.cost >= candidate.cost)
		{
			candidate = neighbor;
		}

		std::cout << " > iteration "<< iter + 1 << ", best=" << candidate.cost << std::endl;

		if (static_cast<size_t>(candidate.cost) == num_bits)
			break;
	}
}


int main(int argc, char* argv[])
{
	// problem configuration
	const size_t num_bits = 64;
	// algorithm configuration
	const size_t max_iterations = 1000;
	// execute the algorithm
	candidate_solution best;
	search(best, max_iterations, num_bits);

	std::cout << "Done. Best Solution: c=" << best.cost << ", v=" << best.vector.c_str() << std::endl;

	return 0;
}
