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
  ind_p ind;
  uint* in_out;
  char* covering;
  uint card, n;

  /* a troolean value :
   * 0 -> not ok
   * 1 -> is ok
   * -1 -> not sure*/
  int is_covering;

  int is_connected;
} sol_t;

typedef sol_t* sol_p;

prob_p prob_from_file(char* path, uchar r);

void prob_free(prob_p p);

sol_p sol_empty(prob_p p);

int sol_verify(prob_p p, sol_p sol);

void sol_add(prob_p p, sol_p res, sol_p old, uint i);

void sol_rm(prob_p p, sol_p res, sol_p old, uint i);

void sol_rand_neigh(prob_p p, sol_p neigh, sol_p old);

void sol_fetch(prob_p p, sol_p sol, char* path);

void sol_free(sol_p sol);

#endif   /* ----- #ifndef problem_INC  ----- */
