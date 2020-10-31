/*
 * =====================================================================================
 *
 *       Filename:  algo.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/10/2020 11:05:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#ifndef  algo_INC
#define  algo_INC

#include "utils.h"
#include "problem.h"
#define MAX_TRY 10
#define NB_IT_COEFF 42

/* Ensure : res contains a valid solution at the end.
 * Require : select must return an elt from a queue and update it.
 * */
void greedy(sol_p res,
    uint (*select)(sol_p, void*),
    void* arg);

void sim_annealing(sol_p s0, 
    float t0,
    float mu,
    uint (*nb_it)(prob_p),
    int (*neigh)(sol_p));

void ant_colony(prob_p p, sol_p res, 
    void (*ant_ia)(prob_p, sol_p, float*),
    void (*local_search)(prob_p, sol_p),
    void (*evap)(float*, void*),
    void* evap_arg);

uint select_best(sol_p sol, void* arg);

/* cumulatives sums of score s, random int between 0 and s
 * if arg != NULL it's where the pheromone vector is passed.
 * WARNING malloc;*/
uint select_fortune_wheel(sol_p sol, void* arg);



#endif   /* ----- #ifndef algo_INC  ----- */
