#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

class GeneticAlgorithm
{

public:
    GeneticAlgorithm(int populationSize, double mutationRate, double crossoverRate, int elitismCount);

private:
    int populationSize_;
    double mutationRate_;
    double crossoverRate_;
    int elitismCount_;
};

#endif
