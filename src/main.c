/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/11/2020 11:13:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algo.h"

#define NB_RUNS 1

int double_compare(const void* x, const void* y){
  double* fx = (double*)x;
  double* fy = (double*)y;

  if((*fx - *fy) > 0.0001)
    return 1;
  
  if((*fx - *fy) < -0.0001)
    return -1;

  return 0;
}

double* quartiles(double* t, uint n){
  double* res = malloc(3*sizeof(double));
  qsort((void*)t, (size_t) n, sizeof(double), double_compare);
  res[0] = t[n>>2];
  res[2] = t[(3*n)>>2];
  res[1] = t[n>1];

  return res;
}

int main(int argc, char** argv){
#ifdef RAND
  printf("RAND WHEEL\n");
#endif
  int i;
  char ra; 
  char ro;
  char k;
  clock_t t1;
  int test;
  char buf[1000];
  double* tps;
  double* value;
  double* qtps;
  double* qvalue;
  uint min;
  prob_p prob;
  sol_p cur;
  FILE* stream;
  FILE* stream2;

  srand(time(NULL));

  if(argc == 1)
    return 0;

  for(i=1; i<argc; i++){
    sprintf(buf, "../instances/%s", argv[i]);
    stream = fopen(buf, "r");
    if(!stream)
      continue;

    fclose(stream);
#ifdef RAND
    sprintf(buf, "../rand_results/res_%d_%d_%s", ANT_NUMBER, TMAX, argv[i]);
#else
    sprintf(buf, "../results/res_%d_%d_%s", ANT_NUMBER, TMAX, argv[i]);
#endif
    stream = fopen(buf, "w");
    if(!stream)
      continue;

#ifdef RAND
    sprintf(buf, "../rand_results/time_%d_%d_%s", ANT_NUMBER, TMAX, argv[i]);
#else
    sprintf(buf, "../results/time_%d_%d_%s", ANT_NUMBER, TMAX, argv[i]);
#endif
    stream2 = fopen(buf, "w");
    if(!stream2)
      continue;

    fprintf(stream, "ANT_NUMBER : %d\nNB_IT : %d\nNB_RUNS : %d\n#k ra ro MIN Q1 MEDIANE Q3 \n", 
        ANT_NUMBER, TMAX, NB_RUNS);
    
    fprintf(stream2, "ANT_NUMBER : %d\nNB_IT : %d\nNB_RUNS : %d\n#ka ra ro Q1 MEDIANE Q3 \n", 
        ANT_NUMBER, TMAX, NB_RUNS);

    sprintf(buf, "../instances/%s", argv[i]);

    for(k=1; k<4; k++){
      for(ra=1; ra<3; ra++){
        for(ro=ra; ro<ra+2; ro++){
          prob = prob_from_file(buf, ra, ro, k);
          tps = malloc(NB_RUNS*sizeof(double));
          value = malloc(NB_RUNS*sizeof(double));
          min = 10000;
          for(test=0; test<NB_RUNS; test++){
            cur = sol_empty(prob);
            t1 = clock();
            ant_colony(cur, ANT_NUMBER, TMAX);
            t1 = clock() - t1;

            tps[test] = (double) t1 / (double) CLOCKS_PER_SEC;
            value[test] = (double) cur->card;

            if(cur->card < min)
              min = cur->card;

            sol_free(cur);
          }

          qtps = quartiles(tps, NB_RUNS);
          qvalue = quartiles(value, NB_RUNS);

          fprintf(stream2, "%d %d %d %lf %lf %lf\n",
              k, ra, ro, qtps[0], qtps[1], qtps[2]);

          fprintf(stream, "%d %d %d %d %d %d %d\n", k, ra, ro,
              min, (uint) qvalue[0], (uint) qvalue[1], (uint) qvalue[2]);

          prob_free(prob);
          free(tps);
          free(value);

          free(qtps);
          free(qvalue);
        }
      }
    }
    fclose(stream);
  }

  return 0;
}
