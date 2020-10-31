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

void greedy(sol_p res, 
    uint (*select)(sol_p, void*), 
    void* arg){

  while((res->remaining > 0) && (QUEUE_CARD(res->queue)>0))
    sol_add_select(res, select, arg);

  if(res->remaining > 0){
    printf("non connected input\n");
    EXIT_ERROR("greedy");
  }
}

void sim_annealing(sol_p s0,
    float t0,
    float mu,
    uint (*nb_it)(prob_p)){

  sol_p current;
  sol_p neigh;
  uint k, i;
  int flag, delta;
  float rd, temp;

  current = sol_empty(s0->prob);
  neigh = sol_empty(s0->prob);
  sol_copy(current, s0);
  sol_copy(neigh, s0);

  k = nb_it(s0->prob);
  temp = t0;

  for(k; k > 0; k --){
    /* update neigh */
    sol_copy(neigh, current);

    /* compute a neighbour */
    for(i=0; i < MAX_TRY; i++){
      flag = sol_neigh(neigh);
      if(flag)
        break;
    }

    delta = neigh->card - curent->card;

    /* If nothing changed no need to update the solutions */
    if (!delta)
      continue;

    rd = RAND_UNIF_01; 
    if(delta < 0 || (rd < exp((float)delta / temp))){
      /* update local opt */
      sol_copy(current, neigh);

      if(current->card < s0->card)
        /* update global opt */
        sol_copy(s0, current);
    }

    temp *= mu;
  }

  sol_free(current);
  sol_free(neigh);
}

uint select_best(sol_p sol, void* arg){
  uint k;
  uint best, cur;
  uint index;
  uint* v;

  if(!QUEUE_CARD(sol->queue)){
    fprintf(stderr, "sol->queue is empty\n");
    EXIT_ERROR("select_best");
  }

  best = sol_score(sol, sol->queue->data[queue->bot]);
  QUEUE_ITER(sol->queue, v){
    cur = sol_score(sol, *v);
    if(cur > best){
      best = cur;
      index = k; 
    }
  }

  return index;
}

/* Let t be a sorted set of n floats
 * return the index of the interval of containing x */
uint dich_spot(float* t, float x, uint n){
  uint a = 0;
  uint b = n-1;
  uint m;

  while(b > a)
  {
    m = (a+b)>>1;

    if((x >= t[m])  && (x < t[m+1]))
      return m;

    if(x < t[m])
      b = m;
    /* x bigger than t[m+1] */
    else
      a = m+1;
  }
  return 0;

}

uint select_fortune_wheel(sol_p sol, void* arg){
  /* length queue_card  + 1 */
  /*  */
  float* acc_score;
  float random;
  uint* v;
  uint q_card;
  uint k;

  q_card = QUEUE_CARD(sol->queue);

  if(q_card){
    fprintf(stderr, "sol->queue is empty\n");
    EXIT_ERROR("select_fortune_wheel");
  }

  acc_score = malloc(sizeof(float)*(q_card + 1));
  acc_score[0] = 0;

  k = 1;
  QUEUE_ITER(sol->queue, v){
    acc_score[k] = acc_score[k-1] + (float) sol_score(sol, *v);
    /* If arg non NULL, we add the pheromon value */
    acc_score[k] += arg ? arg[*v] : 0;
    k++;
  }

  random = RAND_FLOAT(0, acc_score[q_card]); 
  k = dich_spot(acc_score, random, q_card+1);
  return k;
}

/* TODO the coeff Q on th pheromone part is given by const*n/nb_ant */
