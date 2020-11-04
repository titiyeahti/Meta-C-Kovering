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

void print_tab(char* t, uint n){
  uint i;
  for(i=0; i<(n>>1); i++){
    printf("%d ", t[i]);
  }
  printf("\n");
}

prob_p prob_from_file(char* path, char ra, char ro, char k){
  prob_p res;
  uint n;
  res = malloc(sizeof(prob_t));
  res->coord = coord_from_file(path, &n);
  res->cover = graph_from_coord(res->coord, ra, n);
  res->connect = graph_from_coord(res->coord, ro, n);
  res->ra = ra;
  res->ro = ro;
  res->k = k;
  res->n = n;

  return res;
}

void prob_free(prob_p p){
  graph_free(p->cover);
  graph_free(p->connect);
  free(p->coord);
  p->coord = NULL;
  free(p);
  p = NULL;
}

sol_p sol_empty(prob_p p){
  uint k;
  uint *v;
  sol_p res;

  res = malloc(sizeof(sol_t));

  res->prob = p;

  res->ind = IND_NEW(p->n);
  IND_CLEAR(res->ind, p->n, k);
  
  res->in_queue = IND_NEW(p->n);
  IND_CLEAR(res->in_queue, p->n, k);

  res->queue = queue_new(p->n);

  IND_SET(res->ind, 0);

  FOR_ALL_NEIGH(p->connect, 0, v){
    queue_push(res->queue, *v);
    IND_SET(res->in_queue, *v);
  }

  res->cover = malloc((p->n)*sizeof(char));
  res->score = malloc((p->n)*sizeof(uint));
  
  for(k=0; k<p->n; k++)
    res->cover[k] = 0;

  for(k=0; k<p->n; k++)
    res->score[k] = sol_compute_score(res, k);

  res->score[0] = 0;

  res->card = 0;
  res->remaining = p->n - 1;

  return res;
}

int sol_is_connected(sol_p sol){
  int res = graph_is_connected_subgraph(sol->prob->connect, sol->ind);
  
  return res;
}

uint sol_compute_score(sol_p sol, uint i){
  uint res = 0;
  uint* v = NULL;

  if(sol->cover[i] < sol->prob->k)
    res ++;

  FOR_ALL_NEIGH(sol->prob->cover, i, v){
    /* the well, 0 does not count */
    if(*v && (sol->cover[*v] <  sol->prob->k))
      res ++;
  }

  return res;
}

void sol_copy(sol_p dest, sol_p src){
  if(dest->prob->n != src->prob->n){
    EXIT_ERROR("sol_copy");
  }
  dest->prob = src->prob; 
  queue_copy(dest->queue, src->queue);
  IND_COPY(dest->ind, src->ind, src->prob->n);
  IND_COPY(dest->in_queue, src->in_queue, src->prob->n);
  memcpy(dest->cover, src->cover, src->prob->n * sizeof(char));
  memcpy(dest->score, src->score, src->prob->n * sizeof(uint));
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
  IND_UNSET(sol->in_queue, cur);

  /* update ind */
  IND_SET(sol->ind, cur);
  /* update card */
  sol->card ++;
  

  FOR_ALL_NEIGH(sol->prob->connect, cur, v){
    /* if *v is neither in the queue nor in the curent sol (ind) */
    if(!(IND_TEST(sol->in_queue, *v) || IND_TEST(sol->ind, *v))){
      queue_push(sol->queue, *v);
      IND_SET(sol->in_queue, *v);
    }
  }

  /* update cover & remaining */
  sol->cover[cur] ++;
  /* if cur is covered */
  if((sol->cover[cur] == sol->prob->k)&& cur )
    sol->remaining --;

  if(sol->score[cur])
    sol->score[cur]--;

  FOR_ALL_NEIGH(sol->prob->cover, cur, v){
    sol->cover[*v] ++;
    if((sol->cover[*v] == sol->prob->k)&&(*v))
      sol->remaining --;
    
    if(sol->score[*v])
      sol->score[*v]--;
  }
}

void sol_add_select(sol_p sol, 
    uint(*select)(sol_p, void*),
    void* arg){
  uint index;

  index = select(sol, arg);

  sol_add_queue_id(sol, index);
}

int sol_rand_neigh(sol_p sol){
  uint nb_neigh, rd, qcard, k;
  uint* v;

  qcard = QUEUE_CARD(sol->queue);
  nb_neigh = sol->card + qcard;
  rd = RAND_UINT(nb_neigh);

  if(rd < qcard){
    sol_add_queue_id(sol, rd);
    return 1;
  }
  else {
    /* select a vertex to remove */
    rd = rd - qcard;
    for(k=0; k<sol->prob->n; k++){
      if(IND_TEST(sol->ind, k)){
        if(rd == 0){
          rd = k;
          break;
        }
        rd --;
      }
    }

    /* cover constraint */
    FOR_ALL_NEIGH(sol->prob->cover, rd, v){
      if((sol->cover[*v]-1) < (int)k)
        return 0;
    }

    /* connectivity constraint */
    IND_UNSET(sol->ind, rd);
    if(sol_is_connected(sol)){
      /* update everything */
      sol->card --;
      queue_push(sol->queue, rd);
      IND_SET(sol->in_queue, rd);
      FOR_ALL_NEIGH(sol->prob->cover, rd, v)
        sol->cover[*v] --;
      
      return 1;
    }
    else{
      IND_SET(sol->ind, rd);
      return 0;
    }
  }
}

void sol_free(sol_p sol){
  free(sol->in_queue);
  sol->in_queue = NULL;

  free(sol->ind);
  sol->ind = NULL;

  queue_free(sol->queue);
  free(sol->cover);
  sol->cover = NULL;

  free(sol->score);
  sol->score = NULL;

  free(sol);
  sol = NULL;
}
