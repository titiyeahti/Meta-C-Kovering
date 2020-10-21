/*
 * =====================================================================================
 *
 *       Filename:  file-handler.h
 *
 *    Description:  
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

#include <stdlib.h>
#include <stdio.h>

float* coord_from_file(char* path, unsigned* n);

void coord_print(float* coord, unsigned n);

#endif   /* ----- #ifndef file-handler_INC  ----- */
