/*
 * =====================================================================================
 *
 *       Filename:  indicator.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/10/2020 19:42:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */


#ifndef  indicator_INC
#define  indicator_INC

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char uchar;

typedef uchar* ind_p;

#define IND_NEW(n) (char*) malloc(((n)>>3) * sizeof(char))

#define IND_SET(ind, i) ind[(i)>>3] |= 1<<((i)&7)

#define IND_TEST(ind, i) ind[(i)>>3] & (1<<((i)&7))

#define IND_CARD(ind, n, k, card) \
  card = 0; \
  for(k=0; k<(n); k++) \
    if(IND_TEST(ind, k)) card++

/* Intersection */
#define IND_AND(ind, ind1, ind2, n, k) \
  for(k=0; k<(n)>>3; k++) ind[k] = ind1[k] & ind2[k]

/* Union */
#define IND_OR(ind, ind1, ind2, n, k) \
  for(k=0; k<(n)>>3; k++) ind[k] = ind1[k] | ind2[k]

#define IND_FREE(ind) free(ind)

/* WARNING : n is the number of elements not the size of the array */
#define IND_PRINT(ind, n, k) \
  for(k=0; k<(n); k++) {\
    if(IND_TEST(ind, k)) printf("%d ", k);}\
  printf("\n")

#endif   /* ----- #ifndef indicator_INC  ----- */
