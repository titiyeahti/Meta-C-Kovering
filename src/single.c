/*
 * =====================================================================================
 *
 *       Filename:  single.c
 *
 *    Description:  usage 
 *            make single.out
 *            ./single.out path {k ra ro {ant_nb tmax}} 
 *            you can call this program either with :
 *                * only the path to the input file;
 *                * the path + k, ra, ro;
 *                * the path + k, ra, ra + ant_nb, tmax
 *
 *        Version:  1.0
 *        Created:  04/11/2020 16:02:54
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

int main(int argc, char** argv){
  char ra, ro, k;
  uint ant_nb, tmax;
  clock_t t1;
  prob_p prob;
  sol_p sol;
  if(argc == 1)
    return 0;
  if(argc == 5 || argc == 7){
    k = (char)strtoul(argv[2], NULL, 10);
    ra = (char)strtoul(argv[3], NULL, 10);
    ro = (char)strtoul(argv[4], NULL, 10);
  } else {
    k = 2;
    ra = 2;
    ro = 2;
  }

  if(argc == 7){
    ant_nb = (uint) strtoul(argv[5], NULL, 10);
    tmax = (uint) strtoul(argv[6], NULL, 10);
  } else {
    ant_nb = ANT_NUMBER;
    tmax = TMAX;
  }

  prob = prob_from_file(argv[1], k, ra, ro);
  sol = sol_empty(prob);

  t1 = clock();
  ant_colony(sol, ant_nb, tmax);
  t1 = clock() - t1;

  printf("value : %d, exec_time : %lf\n", 
      sol->card, (double) t1 / (double) CLOCKS_PER_SEC);

  sol_free(sol);
  prob_free(prob);

  return 0;
}
