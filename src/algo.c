/*
 * =====================================================================================
 *
 *       Filename:  algo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/10/2020 10:34:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "algo.h"

void greedy(prob_p p, sol_p res, 
    uint (*select)(queue_p, sol_p, void*), 
    void* arg){
  queue_p q;

  q = queue_new(p->n);
  queue_push(q, 0);

  while(QUEUE_CARD(q) > 0){
    /* choose a vertex to add to sol */
    /* push neigh not in sol into q */
  }

  /* check covering if not  */
}

