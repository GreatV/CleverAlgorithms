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

## How to build the source code

```bash
gcc -g -Wall -std=c++11 <algorithm>.cpp -lstdc++ -o <algorithm>
```
