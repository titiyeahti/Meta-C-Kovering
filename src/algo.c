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

  while((res->remaining > 0) && (QUEUE_CARD(res->queue)>0)){
    sol_add_select(res, select, arg);
  }

  if(res->remaining > 0){
    printf("non connected input\n");
    EXIT_ERROR("greedy");
  }
}

void sim_annealing(sol_p s0, float t0, float mu){

  sol_p current;
  sol_p neigh;
  uint k, i;
  int flag, delta;
  float rd, temp;

  current = sol_empty(s0->prob);
  neigh = sol_empty(s0->prob);
  sol_copy(current, s0);
  sol_copy(neigh, s0);

  k = s0->prob->n * NB_IT_COEFF;
  temp = t0;

  for(k=0; k<s0->prob->n; k++){
    /* update neigh */
    sol_copy(neigh, current);

    /* compute a neighbour */
    for(i=0; i < MAX_TRY; i++){
      flag = sol_rand_neigh(neigh);
      if(flag)
        break;
    }

    delta = neigh->card - current->card;

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

void ant_colony(sol_p res, uint ant_nb, uint tmax){
  float big_q;
  uint i, ant, t;

  /* best sol encountered is stored in best*/
  sol_p best;
  sol_p cur;
  
  float* pherom;
  float* pherom_new;

  best = sol_empty(res->prob);
  cur = sol_empty(res->prob);

  sol_copy(best, res);
  greedy(best, select_best, NULL);

  pherom = malloc(res->prob->n*sizeof(float));
  pherom_new = malloc(res->prob->n*sizeof(float));
  for(i=0; i<res->prob->n; i++){
    pherom[i] = 0;
    pherom_new[i] = 0;
  }

  /* card is proportional with n and k */
  big_q = Q_COEFF * (float) res->prob->n * res->prob->k / (float) ant_nb;

  /* ALGO LIES HERE */
  for(t=0; t<tmax; t++){
    for(ant=0; ant < ant_nb; ant++){
      sol_copy(cur, res);

#ifdef RAND
      greedy(cur, select_fortune_wheel, pherom);
#else
      greedy(cur, select_fortune_wheel, pherom);
#endif

      /* deposit */
      for(i=0; i<res->prob->n; i++){
        if(IND_TEST(cur->ind, i))
          pherom_new[i] += big_q / (float) cur->card;
      }

      /* Update best */
      if(cur->card < best->card)
        sol_copy(best, cur);
    }

    /* evap */
    for(i=0; i<res->prob->n; i++){
      pherom[i] = RHO*pherom[i] + (1-RHO)*pherom_new[i];
      pherom_new[i] = 0;
    }
  }
  /* END OF ALGO */

  sol_copy(res, best);
  sol_free(best);
  sol_free(cur);
  free(pherom);
  free(pherom_new);
}

void ant_colony_sa(sol_p res, uint ant_nb, uint tmax, float t0, float mu){
  float big_q;
  uint i, ant, t;

  /* best sol encountered is stored in best*/
  sol_p best;
  sol_p cur;
  
  float* pherom;
  float* pherom_new;

  best = sol_empty(res->prob);
  cur = sol_empty(res->prob);

  sol_copy(best, res);
  greedy(best, select_best, NULL);

  pherom = malloc(res->prob->n*sizeof(float));
  pherom_new = malloc(res->prob->n*sizeof(float));
  for(i=0; i<res->prob->n; i++){
    pherom[i] = 0;
    pherom_new[i] = 0;
  }

  /* SCORE is proportional with n and k */
  big_q = Q_COEFF * (float) res->prob->n * res->prob->k / (float) ant_nb;

  /* ALGO LIES HERE */
  for(t=0; t<tmax; t++){
    printf("best->card : %d\n", best->card);
    for(ant=0; ant < ant_nb; ant++){
      sol_copy(cur, res);
      greedy(cur, select_fortune_wheel, pherom);
      
      sim_annealing(cur, t0, mu);
      /* deposit */
      for(i=0; i<res->prob->n; i++){
        if(IND_TEST(cur->ind, i))
          pherom_new[i] += big_q / (float) cur->card;
      }

      /* Update best */
      if(cur->card < best->card)
        sol_copy(best, cur);
    }

    /* evap */
    for(i=0; i<res->prob->n; i++){
      pherom[i] = RHO*pherom[i] + pherom_new[i];
      pherom_new[i] = 0;
    }
  }
  /* END OF ALGO */

  sol_copy(res, best);
  sol_free(best);
  sol_free(cur);
  free(pherom);
  free(pherom_new);
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

  best = sol_score(sol, sol->queue->data[sol->queue->bot]);

  k=0;
  index=0;
  QUEUE_ITER(sol->queue, v){
    cur = sol_score(sol, *v);
    if(cur > best){
      best = cur;
      index = k; 
    }

    k++;
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
  float* pherom; 
  float random;
  uint* v;
  uint k;
  uint q_card;

  q_card = QUEUE_CARD(sol->queue);

  if(!q_card){
    fprintf(stderr, "sol->queue is empty\n");
    EXIT_ERROR("select_fortune_wheel");
  }

  pherom = (float*) arg;
  acc_score = malloc(sizeof(float)*(q_card + 1));
  acc_score[0] = 0;


  k = 1;
  QUEUE_ITER(sol->queue, v){
    acc_score[k] = acc_score[k-1] + (float) sol_score(sol, *v);
    /* If arg non NULL, we add the pheromon value */
    acc_score[k] += arg ? pherom[*v] : 0;
    k++;
  }

  random = RAND_FLOAT(0, acc_score[q_card]); 
  k = dich_spot(acc_score, random, q_card+1);
  free(acc_score);
  return k;
}

uint select_rand(sol_p sol, void* arg){
  float* acc_score;
  float* pherom; 
  float random;
  uint* v;
  uint k;
  uint q_card;

  q_card = QUEUE_CARD(sol->queue);

  if(!q_card){
    fprintf(stderr, "sol->queue is empty\n");
    EXIT_ERROR("select_fortune_wheel");
  }

  pherom = (float*) arg;
  acc_score = malloc(sizeof(float)*(q_card + 1));
  acc_score[0] = 0;


  k = 1;
  QUEUE_ITER(sol->queue, v){
    acc_score[k] = acc_score[k-1] + 1.;
    /* If arg non NULL, we add the pheromon value */
    acc_score[k] += arg ? pherom[*v] : 0;
    k++;
  }

  random = RAND_FLOAT(0, acc_score[q_card]); 
  k = dich_spot(acc_score, random, q_card+1);
  free(acc_score);
  return k;
}


/* TODO the coeff Q on th pheromone part is given by const*n/nb_ant */
