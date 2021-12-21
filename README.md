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

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-32.768,%2032.768]">, and <img src="https://render.githubusercontent.com/render/math?math=a=20, b=0.2, c=2\pi">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(0,%20...,%200))

### BUKIN FUNCTION N.6

![bukin function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/bukin_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20100%20\sqrt{|x_2%20-%200.01x_1^2|}%20+%200.01|x_1%20+%2010|)

### CROSS-IN-TRAY FUNCTION

![cross-in-tray function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/cross_in_tray_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-0.0001(|sin(x_1)sin(x_2)e^{|100%20-%20\frac{\sqrt{x_1^2%20+%20x_2^2}}{\pi}|}|%20+%201)^{0.1})

### EGGHOLDER FUNCTION

![egg holder function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/eggholder_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-%20(x_2%20+%2047)%20sin(\sqrt{|x_2%20+%20\frac{x_1}{2}%20+%2047|})%20-%20x_1%20sin(\sqrt{|x_1%20-%20(x_2%20+%2047)|}))

### Gramacy & Lee Function

![gramacy & lee function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/gramacy_lee_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\frac{sin(10\pi%20x)}{2x}%20+%20(x%20-%201)^4)

### Griewank Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/griewank_function_600.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/griewank_function_60.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/griewank_function_6.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i%20=%201}^d%20\frac{x_i^2}{4000}%20-%20\prod\limits_{i%20=%201}^d%20cos(\frac{x_i}{\sqrt{i}})%20+%201)

### Holder Table Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/HOLDER_TABLE_FUNCTION.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-|sin(x_1)%20cos(x_2)%20e^{|1%20-%20\frac{\sqrt{x_1^2%20+%20x_2^2}}{\pi}|}|)

### Levy Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/levy_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20sin^2(\pi%20w_1)+%20\sum\limits_{i%20=%201}^{d%20-%201}{(w_i%20-%201)^2}%20\[%201%20+%2010%20sin^2(\pi%20w_i%20+%201)\]%20+%20(w_d%20-%201)^2%20\[1%20+%20sin^2(2%20\pi%20*%20w_d)\])

![](https://latex.codecogs.com/svg.latex?\Large&space;w_i%20=%201%20+%20\frac{x_i%20-%201}{4},%20\text{for%20all%20$i%20=%201,%20...,%20d$})

### Levy Function N. 13

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/levy_function_n_13.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20sin^2(3%20\pi%20x_1)%20+%20(x_1%20-%201)^2%20\[1%20+%20sin^2(3%20\pi%20x_2)\]%20+%20(x_2%20-%201)^2%20\[%201%20+%20sin^2(2%20\pi%20x_2)\])

### Rastrigin Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/rastrigin_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%2010d%20+%20\sum\limits_{i=1}^d{x_i^2%20-%2010%20cos%20(2%20\pi%20x_i)})

### Schaffer Function N. 2

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/schaffer_function_n_2_100.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/schaffer_function_n_2_2.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%200.5%20+%20\frac{sin^2(x_1^2%20-%20x_2^2)%20-%200.5}{\[%201%20+%200.001%20(x_1^2%20+%20x_2^2)\]^2})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-100, 100] \text{for all} i = 1, 2">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (0, 0)">

### Schaffer Function N. 4

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/schaffer_function_n_4_100.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/schaffer_function_n_4_2.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)=0.5+\frac{cos^2(sin(|x_1^2%20-%20x_2^2|))%20-%200.5}{\[1%20+%200.001%20(x_1^2%20+%20x_2^2)\]^2})


### Schwefel Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/schwefel_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20418.9829d%20-%20\sum\limits_{i=1}^d%20x_i%20sin(\sqrt{|x_i|}))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-500, 500] \text{for all} i = 1, 2">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (420.9687,..., 420.9687)">


### Shubert Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/shubert_function.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/shubert_function_2.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\big(%20\sum\limits_{i=1}^5%20{i%20cos((i%20+%201)%20x_1%20+%20i)}%20\big)%20%20\big(\sum\limits_{i=1}^5%20{i%20cos((i%20+%201)%20x_2%20+%20i)}%20\big))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-5.12, 5.12] \text{for all} i = 1, 2">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = -186.7309">

### Bohachevsky Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/bohackevsky_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20x_1^2%20+%202x_2^2%20-%200.3cos(3%20\pi%20x_1)%20-%200.4cos(4%20\pi%20x_2)%20+%200.7)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-100, 100] \text{for all} i = 1, 2">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (0, 0)">

### Perm Function 0, D, Beta

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/perm_function_0_D_beta.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d{\big(%20\sum\limits_{j=1}^d{(j%20+%20\beta)%20(x_j^i%20-%20\frac{1}{j^i})}%20\big)^2})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-d, d] \text{for all} i = 1, 2">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (1, \frac{1}{2}, ..., \frac{1}{d})">

### Rotated Hyper-ellipsoid Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/rotated_hyper_ellipsoid_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d{\sum\limits_{j=1}^i{x_j^2}})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-65.536, 65.536] \text{for all} i = 1, 2, ..., d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (0, 0, ..., 0)">

## How to build the source code

```bash
gcc -g -Wall -std=c++11 <algorithm>.cpp -lstdc++ -o <algorithm>
```

[![asciicast](https://asciinema.org/a/zwweRbdZSJUDAJEGfuBSKsrHW.svg)](https://asciinema.org/a/zwweRbdZSJUDAJEGfuBSKsrHW)

## Thanks

This project has been supported by JetBrains Free License Programs - Licenses for Open Source Development. Thanks JetBrains!

[![JetBrains](https://resources.jetbrains.com/storage/products/company/brand/logos/jb_beam.svg)]( https://jb.gg/OpenSourceSupport)
