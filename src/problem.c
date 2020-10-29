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
  sol_p res;

  res = malloc(sizeof(sol_p));
  res->ind = IND_NEW(p->n);
  IND_CLEAR(res->ind, p->n, k);
  res->cover = malloc((p->n)*sizeof(char));
  for(k=0; k<p->n; k++)
    res->cover[k] = 0;

  res->n = p->n;
  res->card = 0;
  res->is_connected = 0;
  res->is_covering = 0;

  return res;
}

int sol_is_covering(prob_p p, sol_p sol){
  int i;
  if(sol->is_covering == -1){
    for(i=0; i<p->n; i++){
      if(sol->cover[i]<p->k){
        sol->is_covering = 0;
        return 0;
      }
    }

    sol->is_covering = 1;
    return 1;
  }
  else
    return sol->is_covering;
}

int sol_is_connected(prob_p p, sol_p sol){
  if(sol->is_connected == -1)
    sol->is_connected = graph_is_connected_subgraph(p->connect, sol->ind);
  
  return sol->is_connected;
}

int sol_verify(prob_p p, sol_p sol){
  sol_is_connected(p, sol);
  sol_is_covering(p, sol);
  return (sol->is_covering && sol->is_connected);
}

void sol_copy(sol_p dest, sol_p src){
  if(dest->n != src->n){
    EXIT_ERROR("sol_copy");
  }
  dest->n = src->n; 
  dest->card = src->card; 
  dest->is_covering = src->is_covering; 
  dest->is_connected = src->is_connected; 
  IND_COPY(dest->ind, src->ind, src->n);
  memcpy(dest->cover, src->cover, src->n * sizeof(char));
}

void sol_add(prob_p p, sol_p sol, uint i){
  int flag_a, flag_o, k;
  uint* v;
  if(!(IND_TEST(sol->ind, i))){
    IND_SET(sol->ind, i);
    sol->card ++;
    flag_a = 1;
    flag_o = 0;

    /* Updating cover */
    sol->cover[i] ++;
    flag_a &&= (sol->cover[i] >= p->k);
    FOR_ALL_NEIGH(p->cover, i, v){
      sol->cover[*v] ++;
      flag_a &&= (sol->cover[*v] >= p->k);
    }

    if(sol->is_covering != 1)
        sol->is_covering = flag_a ? -1 : 0;

    /* Short connection test */
    FOR_ALL_NEIGH(p->connect, i, v){
      if(IND_TEST(sol->ind, *v))
        flag_o ||= 1;
    }

    if(flag_o)
      sol->connected = sol->connected ? sol->connected : -1;
    else 
      sol->connected = 0;
  }
}

void sol_rm(prob_p p, sol_p sol, uint i){
  int flag_a, k;
  uint* v;
  if(IND_TEST(sol->ind, i)){
    IND_UNSET(sol->ind, i);
    sol->card --;

    sol->cover[i] --;
    flag_a &&= (sol->cover[i] >= p->k);
    FOR_ALL_NEIGH(p->cover, i, v){
      sol->cover[*v] --;
      flag_a &&= (sol->cover[i] >= p->k);
    }
    
    if(sol->is_covering != 1)
      sol->is_covering = flag_a ? -1 : 0;
    else 
      sol->is_covering = flag_a;
  }
}

void sol_rand_neigh(prob_p p, sol_p sol){
  EXIT_ERROR("sol_rand_neigh");
}

void sol_fetch(prob_p p, sol_p sol, char* path){
  EXIT_ERROR("sol_fetch");
}

void sol_free(sol_p sol){
  free(sol->ind);
  free(sol->cover);
  free(sol);
}
