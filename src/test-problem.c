/*
 * =====================================================================================
 *
 *       Filename:  test-problem.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2020 21:49:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "problem.h"

int main(void){
  char ra, ro, k;
  ra = 1;
  ro = 2;
  k = 3;
  prob_p p;
  sol_p sol;
  p = prob_from_file("../instances/captANOR150_7_4.dat", ra, ro, k);
  graph_print(p->connect);
  graph_print(p->cover);
  sol = sol_empty(p);

  printf("coucou\n");
  sol_free(sol);

  return 0;
}

