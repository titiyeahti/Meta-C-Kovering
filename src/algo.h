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


/* Ensure : res contains a valid solution at the end.
 * Require : select must return an elt from a queue and update it.
 * */
void greedy(prob_p p, sol_p res,
    uint (*select)(sol_p, void*),
    void* arg);

void sim_annealing(prob_p p, sol_p res, 
    sol_p s0, 
    float t0,
    float mu,
    uint (*nb_it)(prob_p),
    sol_p (*neigh)(prob_p, sol_p));

void ant_colony(prob_p p, sol_p res, 
    void (*ant_ia)(prob_p, sol_p, float*),
    void (*local_search)(prob_p, sol_p),
    void (*evap)(float*, void*),
    void* evap_arg);

#endif   /* ----- #ifndef algo_INC  ----- */
