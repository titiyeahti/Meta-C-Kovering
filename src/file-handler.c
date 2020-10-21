/*
 * =====================================================================================
 *
 *       Filename:  file-handler.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/10/2020 10:49:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "file-handler.h"

float* coord_from_file(char* path, unsigned* n){
  FILE* stream;
  int ret;
  unsigned i;
  float x, y;
  float* coord;
  stream = fopen(path, "r");
  if(!stream)
    printf("could not open : %s\n", path);

  *n = 0;
  ret = fscanf(stream, "%d %f %f", &i, &x, &y);
  while (*n == i){
    printf("%d %d %f %f \n", *n, i, x, y);
    (*n) ++;
    ret = fscanf(stream, "%d %f %f", &i, &x, &y);
  }

  coord = malloc(2*(*n)*sizeof(float));
  rewind(stream);

  for(i=0; i<*n; i++)
    fscanf(stream, "%d %f %f\n", &ret, 
        coord + 2*i, coord + 2*i + 1);

  fclose(stream);

  return coord;
}

void coord_print(float* coord, unsigned n){
  int i;
  for(i=0; i<n; i++){
    printf("x_%d = (%f, %f)\n", i, coord[2*i], coord[2*i+1]);
  }
}
