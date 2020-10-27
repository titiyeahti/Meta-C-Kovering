/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/10/2020 17:55:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, MPRO
 *
 * =====================================================================================
 */

#ifndef  graph_INC
#define  graph_INC

#include "utils.h"
#include "indicator.h"
#include "file-handler.h"
#include "queue.h"

/* this structure represent a graph G=(V,E) with |V| = n and |E| = m;
 * STATIC structure do not try to modify an existing one*/
typedef struct graph {
  /* the number of vertices in the graph */
  uint n;

  /* vertices, an array of length n+1;
   * vertices[i+1] - vertices[i] = number of neighbours of i;
   * vertices[n] = m;*/
  uint * vertices;

  /* edges, an array of length m;
   * form edges[vertices[i]] to edges[vertices[i+1]-1]
   * you obtain the neighbours of i;*/
  uint * edges;
} graph_t;

typedef graph_t * graph_p;

/* returns the degree of i in G*/
#define DEG(G, i)\
  (G->vertices[i+1] - G->vertices[i])

/* after call, N points to the neighbours' array of i of size d */
#define NEIGHS(G, i, N, d)\
  N = G->edges + G->vertices[i]; d = DEG(G, i)

/* iterate over the pointer to neighbour */
#define FOR_ALL_NEIGH(G, i, n)\
  for(n = G->edges + G->vertices[i]; \
      n < G->edges + G->vertices[i+1]; \
      n++)

/* A subgraph SG is represented as the tupple G, ind, where ind indicate 
 * whether or not a vertex of G is in SG*/

graph_p graph_new(uint n);

graph_p graph_subgraph(graph_p g, ind_p ind);

void graph_connect(graph_p g, ind_p); 

void graph_dfs(graph_p g, ind_p ind, uint v, 
    void(*f)(uint, void*), void* arg)

int graph_is_connected_subgraph(graph_p g, ind_p ind);

graph_p graph_from_coord(float* coord, char r, uint n);

graph_p graph_from_file(char* path, char r);

void graph_free(graph_p g);

void graph_print(graph_p g);

void graph_print_subgraph(graph_p g, ind_p ind);

#endif   /* ----- #ifndef graph_INC  ----- */
