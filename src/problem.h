/*
 * =====================================================================================
 *
 *       Filename:  problem.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/10/2020 11:46:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#ifndef  problem_INC
#define  problem_INC

#include "queue.h"
#include "utils.h"
#include "indicator.h"
#include "file_handler.h"
#include "graph.h"

typedef struct prob{
  /* graph modeling the covering potential of each captor */
  graph_p cover;

  /* graph modeling the connection between each captor */
  graph_p connect;

  /* array containing the input */
  float* coord;

  /* ra, detection radius
   * ro, communication radius
   * k, number of needed captor for each point*/
  char ra, ro, k;

  /*  */
  uint n;
} prob_t;

typedef prob_t* prob_p;

typedef struct sol{
  prob_p prob;
  ind_p ind;
  ind_p in_queue;
  queue_p queue;
  char* cover;
  uint card;
  uint remaining;
} sol_t;

typedef sol_t* sol_p;

prob_p prob_from_file(char* path, char ra, char ro, char k);

void prob_free(prob_p p);

#define SOL_SCORE(sol, i) MAX(sol->prob->k - sol->cover[i], 0)

sol_p sol_empty(prob_p p);

#define SOL_COVERS(sol) (sol->remaining <= 0)

int sol_is_covering(sol_p sol);

int sol_is_connected(sol_p sol);

void sol_copy(sol_p dest, sol_p src);

void sol_add_queue_id(sol_p sol, uint i);

void sol_add_select(sol_p sol, 
    uint(*select)(sol_p, void*), 
    void* arg);

/* select a random valid neighbour of sol :
 * */
void sol_rand_neigh(sol_p sol);

void sol_fetch(sol_p sol, char* path);

void sol_free(sol_p sol);

#endif   /* ----- #ifndef problem_INC  ----- */
