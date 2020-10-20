/*
 * =====================================================================================
 *
 *       Filename:  test-ind.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/10/2020 00:37:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "indicator.h"

int main(void){
  int n = 49;
  int k;
  int card;
  ind_p ind = IND_NEW(n);

  IND_SET(ind, 0);
  IND_SET(ind, 19);
  IND_SET(ind, 23);

  IND_PRINT(ind, n, k);

  ind_p ind1 = IND_NEW(n);
  ind_p ind2 = IND_NEW(n);

  IND_SET(ind1, 0);
  IND_SET(ind2, 0);
  IND_SET(ind1, 19);
  IND_SET(ind2, 23);

  IND_AND(ind, ind1, ind2, n, k);
  IND_PRINT(ind, n, k);

  IND_OR(ind, ind1, ind2, n, k);
  IND_PRINT(ind, n, k);

  IND_CARD(ind, n, k, card);
  printf("%d\n", card);

  free(ind);
  free(ind1);
  free(ind2);

  return EXIT_SUCCESS;
}

