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

### Valid inputs
A valid input is of the form (i x y\\n)\* with i an integer and x, y two floats.
Moreover the on the first row, (x,y) should be (0, 0).

## File Organisation
- `src/` contains the sources of the project;
- `bin/` contains the makefile and the binary files;
- `results/` is where the results are stored;
- `instances/` some instances for the project.

## Usage
### Compilation 

To compute the different executables of the projet, you can simply do : 
```
$cd bin
$make {RAND=1}
```
If you chose to set RAND to 1, the construction procedure will be more randomised (but with very little differences in practice).

### Execution 
There is two executables in this project.

#### main.out
`main.out {input files}` will run the algorithm on each different combination of (R_a, R_o, k) and store the results in `{rand_}results/`. 
The input file must be located in `instances/` and you should only pass the filename to the executable. Check the Makefile for more details 

#### single.out
`single.out` runs the algorithm for the given parameters, prints out the result. Check the Makefile and `src/single.c` for more details.

## Contributors

- Yuli Daune-Funato
- Thibaut *Yéti* MILHAUD

