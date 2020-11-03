/*
 * =====================================================================================
 *
 *       Filename:  test-graph.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2020 21:15:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "graph.h"
#include "utils.h"
#include "indicator.h"
#include "file-handler.h"
#include "queue.h"

int main(){
  uint n;
  char r = 1;
  graph_p g = graph_from_file("../instances/captANOR150_7_4.dat", r);

  graph_print(g);

  graph_free(g);

  return 0;
}

