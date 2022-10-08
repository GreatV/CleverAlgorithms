#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> distribution(0.0, 1.0);
auto random_ = []() { return distribution(generator); };


using prediction_storage = struct prediction_st
{
	double sum = 0.0;
	double count = 0.0;
	double weight = 0.0;
};


typedef std::map<std::string, prediction_storage> prediction_solution;


using classifier_solution = struct classifier_solution_t
{
	std::string condition;
	std::string action;
	size_t lasttime = 0;
	double pred = 0.0;
	double error = 0.0;
	double fitness = 0.0;
	double exp = 0;
	size_t setsize = 0;
	size_t num = 0;
	double dvote = 0.0;
};



int neg(const int bit)
{
	return bit == 1 ? 0 : 1;
}


int target_function(const std::string & s)
{
	const size_t n = s.size();
	int * ints = static_cast<int*>(malloc(sizeof(int) * n));
	for(size_t i = 0; i < n; ++i)
	{
		ints[i] = s[i] - 48;
	}

	auto tmp = (neg(ints[0]) * neg(ints[1]) * ints[2] + neg(ints[0]) * ints[1] * ints[3] 
		+ ints[0] * neg(ints[1]) * ints[4] + ints[0] * ints[1] * ints[5]);
	free(ints);

	return tmp;
}


void new_classifier(classifier_solution & other, const std::string & condition,
	const std::string & action, const size_t gen, const double p1 = 10.0,
	const double e1 = 0.0, const double f1 = 10.0)
{
	other.condition = condition;
	other.action = action;
	other.lasttime = gen;
	other.pred = p1;
	other.error = e1;
	other.fitness = f1;
	other.exp = 0.0;
	other.setsize = 1;
	other.num = 1;
}


void copy_classifier(classifier_solution & child, const classifier_solution & parent)
{
	child.condition = parent.condition;
	child.action = parent.action;
	child.lasttime = parent.lasttime;
	child.pred = parent.pred;
	child.error = parent.error;
	child.fitness = parent.fitness;
	child.exp = 0.0;
	child.setsize = parent.setsize;
	child.dvote = parent.dvote;
	child.num = 1;
}


void random_bitstring(std::string & bitstring, const size_t size = 6)
{
	bitstring.clear();
	bitstring.resize(size);
	for(size_t i = 0; i < size; ++i)
	{
		bitstring[i] = random_() < 0.5 ? '1' : '0';
	}
}


double calculate_deletion_vote(classifier_solution & classifier, const std ::vector<classifier_solution> & pop,
	const double del_thresh, const double f_thresh = 0.1)
{
	auto  vote = classifier.setsize * classifier.num;
	double total = 0;
	for (const auto& i : pop)
	{
		total += i.num;
	}

	double avg_fitness = 0.0;
	for(const auto & item: pop)
	{
		avg_fitness += item.fitness;
	}
	avg_fitness /= total;

	const auto derated = classifier.fitness / classifier.num;
	if(classifier.exp > del_thresh && derated < f_thresh * avg_fitness)
	{
		return vote * (avg_fitness / derated);
	}

	return vote;
}


void delete_from_pop(std::vector<classifier_solution> & pop, const size_t pop_size,
	const double del_thresh = 20.0)
{
	double total = 0.0;
	for(const auto & item : pop)
	{
		total += item.num;
	}
	if(total <= pop_size)
	{
		return;
	}

	double vote_sum = 0.0;
	for(auto & item : pop)
	{
		item.dvote = calculate_deletion_vote(item, pop, del_thresh);
		vote_sum += item.dvote;
	}

	const size_t point = static_cast<size_t>(vote_sum * random_());
	vote_sum = 0.0;
	size_t index = 0;
	for(size_t i = 0; i < pop.size(); ++i)
	{
		vote_sum += pop[i].dvote;
		if(vote_sum >= point)
		{
			index = i;
			break;
		}
	}
	if (pop[index].num > 1)
	{
		pop[index].num -= 1;
	}
	else
	{
		pop.erase(pop.begin() + static_cast<int>(index));
	}
}


void generate_random_classifier(classifier_solution & classifier, const std::string & input,
	const std::vector<std::string> & actions, const size_t gen, const double rate = 1.0 / 3.0)
{
	std::string condition;
	for(auto & c : input)
	{
		condition.push_back(random_() < rate ? '#' : c);
	}
	const std::string action = actions[static_cast<size_t>((actions.size() - 1) * random_())];
	new_classifier(classifier, condition, action, gen);
}


bool does_match(const std::string & input, const std::string & condition)
{
	for(size_t i = 0; i < input.size(); ++i)
	{
		if(condition[i] != '#' && input[i] != condition[i])
		{
			return false;
		}
	}
	return true;
}


void get_actions(std::vector <std::string > & actions, const std::vector<classifier_solution> & pop)
{
	actions.clear();
	for(auto & item : pop)
	{
		if(std::find(actions.begin(), actions.end(), item.action) == actions.end())
		{
			actions.push_back(item.action);
		}
	}
}


void generate_match_set(std::vector<classifier_solution> & match_set, 
	const std::string & input, std::vector<classifier_solution> & pop,
	const std::vector<std::string> & all_actions, const size_t gen,
	const size_t pop_size)
{
	match_set.clear();
	for(const auto & c : pop)
	{
		if (does_match(input, c.condition))
			match_set.push_back(c);
	}
	std::vector <std::string> actions;
	get_actions(actions, match_set);
	while(actions.size() < all_actions.size())
	{
		std::vector<std::string> remaining;
		std::set_difference(all_actions.begin(), all_actions.end(),
			actions.begin(), actions.end(),
			std::back_inserter(remaining));
		classifier_solution classifier;
		generate_random_classifier(classifier, input, remaining, gen);
		pop.push_back(classifier);
		match_set.push_back(classifier);
		delete_from_pop(pop, pop_size);
		actions.push_back(classifier.action);
	}
}


void generate_prediction(prediction_solution pred, const std::vector<classifier_solution> & match_set)
{
	for(auto & classifier : match_set)
	{
		auto key = classifier.action;
		prediction_storage ps;
		pred.insert({ key, ps });
		pred[key].sum += classifier.pred * classifier.fitness;
		pred[key].count += classifier.fitness;
	}

	for(auto & item: pred)
	{
		item.second.weight = 0.0;
		if(item.second.count > 0)
		{
			item.second.weight = item.second.sum / item.second.count;
		}
	}
}

void select_action(std::string & key, const prediction_solution & predictions, const bool p_explore = false)
{
	
}


void search()
{
}


int main(int argc, char* argv[])
{
	return 0;
}
