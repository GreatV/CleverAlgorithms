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

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[-15,%205],x_2\in[-3,3]">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(-10,%201))

### CROSS-IN-TRAY FUNCTION

![cross-in-tray function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/cross_in_tray_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-0.0001(|sin(x_1)sin(x_2)e^{|100%20-%20\frac{\sqrt{x_1^2%20+%20x_2^2}}{\pi}|}|%20+%201)^{0.1})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-2.06261,%20\text{at}%20x^{*}%20=%20(1.3491,%20-1.3491),(1.3491,%201.3491),(-1.3491,%201.3491),\text{and}(-1.3491,%20-1.3491))

### Drop-Wave Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/drop_wave_function_5.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/drop_wave_function_2.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-\frac{1%20+%20cos(12\sqrt{x_1^2%20+%20x_2^2})}{0.5%20(x_1^2%20+%20x_2^2)%20+%202})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-5.12,%205.12]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-1,%20\text{at}%20x^{*}%20=%20(0,%200))

### EGGHOLDER FUNCTION

![egg holder function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/eggholder_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-%20(x_2%20+%2047)%20sin(\sqrt{|x_2%20+%20\frac{x_1}{2}%20+%2047|})%20-%20x_1%20sin(\sqrt{|x_1%20-%20(x_2%20+%2047)|}))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-512,%20512]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-959.6407,%20\text{at}%20x^{*}%20=%20(512,%20404.2319))

### Gramacy & Lee Function

![gramacy & lee function](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/gramacy_lee_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\frac{sin(10\pi%20x)}{2x}%20+%20(x%20-%201)^4)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x%20\in%20[0.5,%202.5]">.

### Griewank Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/griewank_function_600.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/griewank_function_60.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/griewank_function_6.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i%20=%201}^d%20\frac{x_i^2}{4000}%20-%20\prod\limits_{i%20=%201}^d%20cos(\frac{x_i}{\sqrt{i}})%20+%201)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-600,%20600]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(0,...,%200))

### Holder Table Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/HOLDER_TABLE_FUNCTION.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-|sin(x_1)%20cos(x_2)%20e^{|1%20-%20\frac{\sqrt{x_1^2%20+%20x_2^2}}{\pi}|}|)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-19.2085,%20\text{at}%20x^{*}%20=%20(8.05502,%209.66459),(8.05502,%20-9.66459),(-8.05502,%209.66459),(-8.05502,%20-9.66459))

### Levy Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/levy_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20sin^2(\pi%20w_1)+%20\sum\limits_{i%20=%201}^{d%20-%201}{(w_i%20-%201)^2}%20\[%201%20+%2010%20sin^2(\pi%20w_i%20+%201)\]%20+%20(w_d%20-%201)^2%20\[1%20+%20sin^2(2%20\pi%20*%20w_d)\])

![](https://latex.codecogs.com/svg.latex?\Large&space;w_i%20=%201%20+%20\frac{x_i%20-%201}{4},%20\text{for%20all%20$i%20=%201,%20...,%20d$})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(1,...,%201))

### Levy Function N. 13

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/levy_function_n_13.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20sin^2(3%20\pi%20x_1)%20+%20(x_1%20-%201)^2%20\[1%20+%20sin^2(3%20\pi%20x_2)\]%20+%20(x_2%20-%201)^2%20\[%201%20+%20sin^2(2%20\pi%20x_2)\])

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010]\text{for%20all}i=1,%202">.

**Global Minimum:**

![](https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(1,%201))

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

### Sphere Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/sphere_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d{x_i^2})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-5.12, 5.12] \text{for all} i = 1, 2, ..., d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (0, 0, ..., 0)">

### Sum of Different Powers Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/SUM_OF_DIFFERENT_POWERS_FUNCTION.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d{|x_i|^{i+1}})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-1, 1] \text{for all} i = 1, 2, ..., d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (0, 0, ..., 0)">

### SUM SQUARES FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/SUM_SQUARES_FUNCTION.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d%20{i%20x_i^2})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-5.12, 5.12] \text{for all} i = 1, 2, ..., d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = 0, \text{at} x^{*} = (0, 0, ..., 0)">

### TRID FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/trid_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d%20{(x_i%20-1)^2}%20-%20\sum\limits_{i=2}^d%20{x_i%20x_{i-1}})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i \in [-d^2, d^2] \text{for all} i = 1, 2, ..., d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*}) = -d(d+4)(d-1)/6, \text{at} x_i = i(d + 1 -i) \text{for all } i=1,2,...,d">

### BOOTH FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/booth_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20(x_1%20+%202x_2%20-%207)^2%20+%20(2x_1%20+%20x_2%20-%205)^2)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010]%20\text{for%20all}%20i%20=%201,%202">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(1,%203)">

### BATYAS FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/matyas_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%200.26(x_1^2%20+%20x_2^2)%20-%200.48x_1%20x_2)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010]%20\text{for%20all}%20i%20=%201,%202">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(0,%200)">

### MCCORMICK FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/mccormick_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20sin(x_1%20+%20x_2)%20+%20(x_1%20-%20x_2)^2%20-%201.5x_1%20+%202.5x_2%20+%201)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[-1.5,%204]%20,x_2 \in [-3, 4]">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-1.9133,%20\text{at}%20x^{*}%20=%20(-0.54719,%20-1.54719)">

### POWER OF SUM FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/power_of_sum.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d{[(\sum\limits_{j=1}^d{x_j^i})%20-%20b_i]^2})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[0,%20d]\,\text{for%20all}\,i=1,...,d">.

### ZAKHAROV FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/zakharov_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^d{x_i^2}%20+%20(\sum\limits_{i=1}^d{0.5%20i%20x_i})^2%20+%20(\sum\limits_{i=1}^d%20{0.5%20i%20x_i})^4)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-5,%2010]%20,\text{at%20all}%20i%20=%201,%20...,%20d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(0,...,%200)">

### THREE-HUMP CAMEL FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/three_hump_camel_function.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/three_hump_camel_function_2.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%202x_1^2%20-%201.05x_1^4%20+%20x_1^6/6%20+%20x_1x_2%20+%20x_2^2)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-5,%205]%20,\text{at%20all}%20i%20=%201,%202">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(0,%200)">

### SIX-HUMP CAMEL FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/six_hump_camel_function.png)

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/six_hump_camel_function_2.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\bigl%20(%204%20-%202.1x_1^2%20+%20x_1^4/3%20\bigr%20)x_1^2%20+%20x_1x_2%20+%20(-4%20+%204x_2^2)x_2^2)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[-3,%203]%20,%20x_2%20\in%20[-2,%202]">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-1.0316,\text{at%20}%20x^{*}%20=%20(0.0898,%20-0.7126)%20\text{and}%20(-0.0898,%200.7126)">

### Dixon-Price FUNCTION

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/dixon_price_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20(x_1%20-%201)^2%20+%20\sum\limits_{i=2}^d%20{i%20(2%20x_i^2%20-%20x_{i-1})^2})

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010],%20\text{for%20all%20}%20i%20=%201,%20...,%20d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x_i%20=%202^{-\frac{2^i-2}{2^i}},\text{for}%20i=1,...,d">


### Rosenbrock Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/rosenbrock_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-cos(x_1)cos(x_2)exp(-(x_1%20-%20\pi)^2%20-%20(x_2%20-%20\pi)^2%20))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-10,%2010],%20\text{for%20all%20}%20i%20=%201,%20...,%20d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x_i%20=%20(1,...,1),\text{for}%20i=1,...,d">

### Easom Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/easom_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20\sum\limits_{i=1}^{d-1}[100%20(x_{i+1}%20-%20x_i^2)^2%20+%20(x_i%20-%201)^2])

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-100,%20100],%20\text{for%20all%20}%20i%20=%201,%202">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-1,%20\text{at}%20X^{*}%20=%20(\pi,\pi)">

### Michalewicz Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/michalewicz_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20-%20\sum\limits_{i=1}^d%20sin(x_i)sin^{2m}%20(\frac{i%20x_i^2}{\pi}))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[0,%20\pi],%20\text{for%20all%20}%20i%20=%201,%202,...,d">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=\text{at%20}d%20=%202:%20f(x^{*})%20=%20-1.8013,%20\text{at}%20X^{*}%20=%20(2.20,1.57)">

<img src="https://render.githubusercontent.com/render/math?math=\text{at%20}d%20=%205:%20f(x^{*})%20=%20-4.687658">

<img src="https://render.githubusercontent.com/render/math?math=\text{at%20}d%20=%2010:%20f(x^{*})%20=%20-9.66015">

### Beale Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/beale_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20(1.5%20-%20x_1%20+%20x_1x_2)^2%20+%20(2.25%20-%20x_1%20+%20x_1x_2^2)^2%20+%20(2.625%20-%20x_1%20+%20x_1%20x_2^3)^2)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_i%20\in%20[-4.5,%204.5],%20\text{for%20all%20}%20i%20=%201,%202">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=\text{at%20}d%20=%202:%20f(x^{*})%20=%200,%20\text{at}%20X^{*}%20=%20(3,0.5)">

### Branin Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/branin_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20a(x_2%20-%20b%20x_1%20+%20c%20x_1%20-%20r)^2%20+%20s(1%20-%20t)cos(x_1)%20+%20s)

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[-5,%2010],%20x_2%20\in%20[0,%2015]">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%20-0.397887,%20\text{at}%20x^{*}%20=%20(\pi,12.275),(\pi,2.275)\text{and}(9.42478,2.475)">

### COLVILLE FUNCTION

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20100(x_1^2%20-%20x_2)^2%20+%20(x_1%20-%201)^2%20+%20(x_3%20-1)^2%20+%2090(x_3^2%20-%20x_4)^2%20+%2010.1((x_2%20-%201)^2%20+%20(x_4%20-1)^2)%20+%2019.8(x_2%20-1)(x_4%20-1))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[-10,%2010],\text{for%20all%20}%20i%20=%201,%202,%203,%204">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%200,%20\text{at}%20x^{*}%20=%20(1,1,1,1)">

### Forrester et al. (2008) Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/forrester_08.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20(6x-2)^2%20sin(12x%20-%204))

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[0,%201]">.

### Goldstein-Price Function

![](https://github.com/GreatV/CleverAlgorithms/raw/main/docs/figures/goldstein_price_function.png)

![](https://latex.codecogs.com/svg.latex?\Large&space;f(x)%20=%20[1%20+%20(x_1%20+%20x_2%20+%201)^2%20(19%20-%2014x_1%20+%203x_1^2%20-%2014x_2%20+%206x_1x_2%20+%203x_2^2)]\times[30%20+%20(2x_1%20-%203x_2)^2%20(18%20-%2032x_1%20+%2012x_1^2%20+%2048x_2%20-36x_1x_2%20+%2027x_2^2)])

**Input Domain:**

The function is usually evaluated on the <img src="https://render.githubusercontent.com/render/math?math=x_1%20\in%20[-2,%202],\text{for all} i = 1, 2">.

**Global Minimum:**

<img src="https://render.githubusercontent.com/render/math?math=f(x^{*})%20=%203,%20\text{at}%20x^{*}%20=%20(0,-1)">

## How to build the source code

```bash
gcc -g -Wall -std=c++11 <algorithm>.cpp -lstdc++ -o <algorithm>
```

[![asciicast](https://asciinema.org/a/zwweRbdZSJUDAJEGfuBSKsrHW.svg)](https://asciinema.org/a/zwweRbdZSJUDAJEGfuBSKsrHW)

## Thanks

This project has been supported by JetBrains Free License Programs - Licenses for Open Source Development. Thanks JetBrains!

[![JetBrains](https://resources.jetbrains.com/storage/products/company/brand/logos/jb_beam.svg)]( https://jb.gg/OpenSourceSupport)
