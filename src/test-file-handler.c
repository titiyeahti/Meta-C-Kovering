/*
 * =====================================================================================
 *
 *       Filename:  test-file-handler.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/10/2020 11:12:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "file-handler.h"

int main(void){
  float* coord;
  unsigned n;

  coord = coord_from_file("../captANOR150_7_4.dat", &n);

  coord_print(coord, n);

  free(coord);

  return EXIT_SUCCESS;
}
