#include "genetic_algorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double mutationRate, double crossoverRate, int elitismCount)
    : populationSize_(populationSize), mutationRate_(mutationRate), crossoverRate_(crossoverRate), elitismCount_(elitismCount)
{
}
