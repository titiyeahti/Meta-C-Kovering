/*
 * =====================================================================================
 *
 *       Filename:  file-handler.h
 *
 *    Description:  Interface to load sets of points from files. 
 *
 *        Version:  1.0
 *        Created:  21/10/2020 10:45:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#ifndef  file_handler_INC
#define  file_handler_INC

#include "utils.h"

/* Ensure : the returned pointer contains the coordinates of the points in file.
 * Require : file at path of the form (%i %f %f\n)*. 
 * WARNING : malloc.
 * */
float* coord_from_file(char* path, uint* n);

#define COORD_SQRDIST(c, i, j) \
  (c[2*i] - c[2*j])*(c[2*i] - c[2*j]) + \
  (c[2*i+1] - c[2*j+1])*(c[2*i+1] - c[2*j+1])

void coord_print(float* coord, uint n);

#endif   /* ----- #ifndef file-handler_INC  ----- */
