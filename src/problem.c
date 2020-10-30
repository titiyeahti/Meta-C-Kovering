/*
 * =====================================================================================
 *
 *       Filename:  problem.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27/10/2020 13:08:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "problem.h"

prob_p prob_from_file(char* path, char ra, char ro, char k){
  prob_p res;

  res = malloc(sizeof(prob_s));
  res->coord = coord_from_file(path, &(res->n));
  res->cover = graph_from_coord(res->coord, ra, res->n);
  res->connect = graph_from_coord(res->coord, ro, res->n);
  res->ra = ra;
  res->ro = ro;
  res->k = k;

  return res;
}

void prob_free(prob_p p){
  graph_free(p->cover);
  graph_free(p->connect);
  free(p->coord);
  free(prob_p p);
}

sol_p sol_empty(prob_p p){
  uint k;
  uint *v;
  sol_p res;

  res = malloc(sizeof(sol_p));

  res->prob = p;
  
  res->ind = IND_NEW(p->n);
  IND_CLEAR(res->ind, p->n, k);
  
  res->in_queue = IND_NEW(p->n);
  IND_CLEAR(res->in_queue, p->n, k);

  res->queue = queue_new(p->n);
  FOR_ALL_NEIGH(p->connect, 0, v){
    queue_push(res->queue, *v);
    IND_SET(in_queue, *v);
  }

  res->cover = malloc((p->n)*sizeof(char));
  for(k=0; k<p->n; k++)
    res->cover[k] = 0;

  res->card = 0;
  res->remaining = p->n - 1;

  return res;
}

int sol_is_connected(sol_p sol){
  int res = graph_is_connected_subgraph(sol->prob->connect, sol->ind);
  
  return res;
}

void sol_copy(sol_p dest, sol_p src){
  if(dest->prob->n != src->prob->n){
    EXIT_ERROR("sol_copy");
  }
  dest->prob = src->prob; 
  queue_copy(dest->queue, src->queue);
  IND_COPY(dest->ind, src->ind, src->n);
  IND_COPY(dest->in_queue, src->in_queue, qrc->n);
  memcpy(dest->cover, src->cover, src->n * sizeof(char));
  dest->card = src->card;
  dest->remaining = src->remaining;
}

void sol_add_queue_id(sol_p sol, uint i){
  uint cur;
  uint* v;
  /* check queue 
   * done in queue_pop_id*/

  /* update queue */
  cur = queue_pop_id(sol->queue, i);
  
  /* update in_queue */
  FOR_ALL_NEIGH(sol->prob->connect, cur, v){
    if(!IND_TEST(sol->in_queue, *v)){
      queue_push(sol->queue, *v);
      IND_SET(sol->in_queue, *v);
    }
  }

  /* update ind */
  IND_SET(sol->ind, cur);

  /* update card */
  sol->card ++;

  /* update cover & remaining */
  sol->cover[cur] ++;
  /* if cur is covered AND cur is not 0 the well */
  if((sol->cover[cur] = p->k) && cur)
    sol->remaining --;

  FOR_ALL_NEIGH(sol->prob->cover, cur, v){
    if(!IND_TEST(sol->ind, *v)){
      sol->cover[cur] ++;
      if((sol->cover[*v] = p->k) && cur)
        sol->remaining --;
    }
  }
}

void sol_add_select_id(sol_p sol, 
    uint(*select)(sol_p, void*),
    void* arg){
  uint index;
  index = select(sol, arg);
  sol_add_queue_id(sol, index);
}

void sol_rand_neigh(prob_p p, sol_p sol){
  EXIT_ERROR("sol_rand_neigh");
}

void sol_fetch(prob_p p, sol_p sol, char* path){
  EXIT_ERROR("sol_fetch");
}

void sol_free(sol_p sol){
  prop_free(sol->prob);
  free(sol->ind);
  free(sol->in_queue);
  queue_free(sol->queue);
  free(sol->cover);
  free(sol);
}
