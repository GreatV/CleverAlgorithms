# CleverAlgorithms

The C++ implementation of [Clever Algorithms](https://github.com/clever-algorithms/CleverAlgorithms).

## Overview

**Clever Algorithms: Nature-Inspired Programming Recipes** is an open source book that describes a large number of algorithmic techniques from the the fields of Biologically Inspired Computation, Computational Intelligence and Metaheuristics in a complete, consistent, and centralized manner such that they are accessible, usable, and understandable. This is a repository for the source code (C++ implementation) of the book project.

## Algorithm List

### Stochastic Algorithms

- [x] Random Search
- [x] Adaptive Random Search
- [x] Stochastic Hill Climbing
- [x] Iterated Local Search
- [x] Guided Local Search
- [x] Variable Neighborhood Search
- [x] Greedy Randomized Adaptive Search
- [x] Scatter Search
- [x] Tabu Search
- [x] Reactive Tabu Search

### Evolutionary Algorithms

- [x] Genetic Algorithm
- [ ] Genetic Programming
- [x] Evolution Strategies
- [x] Differential Evolution
- [x] Evolutionary Programming
- [ ] Grammatical Evolution
- [ ] Gene Expression Programming
- [ ] Learning Classifier System
- [ ] Non-dominated Sorting Genetic Algorithm
- [ ] Strength Pareto Evolutionary Algorithm

### Physical Algorithms

- [x] Simulated Annealing
- [x] Extremal Optimization
- [x] Harmony Search
- [x] Cultural Algorithm
- [x] Memetic Algorithm

### Probabilistic Algorithms

- [x] Population-Based Incremental Learning
- [x] Univariate Marginal Distribution Algorithm
- [x] Compact Genetic Algorithm
- [x] Bayesian Optimization Algorithm
- [x] Cross-Entropy Method

### Swarm Algorithms

- [x] Particle Swarm Optimization
- [x] Ant System
- [x] Ant Colony System
- [x] Bees Algorithm
- [x] Bacterial Foraging Optimization Algorithm

### Immune Algorithms

- [x] Clonal Selection Algorithm
- [x] Negative Selection Algorithm
- [x] Artificial Immune Recognition System
- [ ] Immune Network Algorithm
- [ ] Dendritic Cell Algorithm

### Neural Algorithms

- [ ] Perceptron
- [ ] Back-propagation
- [ ] Hopfield Network
- [ ] Learning Vector Quantization
- [ ] Self-Organizing Map

## Test Functions

### ACKLEY FUNCTION

![ackley functions](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/ackley_functions.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)=-a%20e^{%20-b%20\sqrt{%20\frac1d%20\sum\limits_{i=1}^d%20{x_i^2}%20}%20}%20-e^{%20\frac1d%20\sum\limits_{i=1}^d%20{cos(cx_i)}%20}%20+%20a%20+%20e)

### BUKIN FUNCTION N.6

![bukin function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/bukin_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20100%20\sqrt{|x_2%20-%200.01x_1^2|}%20+%200.01|x_1%20+%2010|)

## How to build the source code

```bash
gcc -g -Wall -std=c++11 <algorithm>.cpp -lstdc++ -o <algorithm>
```

https://user-images.githubusercontent.com/17264618/140650676-01246c41-db54-4f3d-b5df-2b008d42c4aa.mp4
