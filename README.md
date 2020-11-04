# MPRO : meta heuristic project 

## Subject : k-covering 

### Problem description

Given 
- S a set of n points in R^2, we will call them targets from now on;
- the point (0,0) always in S is called the p;
- k an integer;
- d(a,b) the euclidian distance between a and b; 
- R_a the detection radius, two points a and b are connected if d(a,b) \leq R_a;
- R_o the communication radius, a is detected by b if d(a,b) \leq R_o.

We must choose a subset S' (captors) of S such that 
- p is in S';
- S' is connected;
- each target in S except p is detected by at least k captors in S'.

### Parameters restrictions
- k \in {1, 2, 3};
- (R_a, R_o) \in {(1, 1), (1, 2), (2, 2), (2, 3)}.

### Goal
The goal here is to implement an heuristic to obtain a good solution for the problem.

## Proposed solution
### Modeling
We choose to model this problem as a pair of non-oriented graphs G_a and G_o. 

## Usage

The main program will run the ant\_colony algorithm on the given input files.
The input files must be in `instances` folder, and you must only specify their name, NOT their path.
The result are stored in `results`.

```
$cd bin 
$make 
$./main.out input_files 
```

## Contributors

- Daune *Yuli* FUNATO
- Thibaut *Yéti* MILHAUD

