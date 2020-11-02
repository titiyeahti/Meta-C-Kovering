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

/* parameter to play with  */
/* used for neighbours in sim annealing*/
#define MAX_TRY 10

/* in sim_annealing for the number of iterations */
#define NB_IT_COEFF 42

/* Ant colony :
 * rho -> evaporation coeff*/
#define RHO .5

/* deposit coeff */
#define Q_COEFF .1


/* Ensure : res contains a valid solution at the end.
 * Require : select must return an index from a queue.
 * */
void greedy(sol_p res,
    uint (*select)(sol_p, void*),
    void* arg);

/* Ensure : simulated annealing algorithm. At the end, s0 contains 
 * a valid solution.
 * Require : mu in ]0, 1[ and more likely in [0.85, à.99]*/
void sim_annealing(sol_p s0, float t0, float mu);

/* Ensure : performs an ant_colony algorithm to compute a solution in res.
 *    There is ant_nb ants and it will perform tmax loop.
 * */
void ant_colony(sol_p res, uint ant_nb, uint tmax);

uint dich_spot(float* t, float x, uint n);

/* Ensure : return the index of the vertex with the best score 
 *    in sol->queue.
 * Require : sol->must not be empty*/
uint select_best(sol_p sol, void* arg);

/* Ensure : return an index of an random chosen elt in sol->queue. 
 *    The probability for an elt to be chosen is :
 *      score(elt) / sum(score(e)) with e in queue.
 *    If arg is not NULL, score(e) = sol_score(e) + arg(e), arg stands
 *    for the pheormon vector
 * Require : arg must be either NULL or 
 *    a float array of length sol->prob ->n */
uint select_fortune_wheel(sol_p sol, void* arg);

#endif   /* ----- #ifndef algo_INC  ----- */
