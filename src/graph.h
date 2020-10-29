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
 * STATIC structure do not try to modify an existing one
 * Remark : the vertex of index 0 represent the point (0, 0)*/
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

/* Ensure : the returned pointer is a brand new graph with n vertices
 * and 0 edges.
 * WARNING : 
 *    * ret->edges == NULL;
 *    * malloc.
 * */
graph_p graph_new(uint n);

/* Ensure : given g a graph and ind a subset of [1..g->n], the returned 
 *    graph is the subgraph containing only the vertices of ind.
 * Require : ind should be a valid indicator of size at least g->n.
 * WARNING : malloc.
 * */
graph_p graph_subgraph(graph_p g, ind_p ind);

/* Ensure : given g and ind, updates ind so that, at the ind, the subgraph
 *    coded by (g, ind union {0}) is connected.
 * Require : validity of ind and g, zero must no be in ind.
 * WARNING : allocates 2 array and free them -> may be slow.
 * */
void graph_connect(graph_p g, ind_p); 

/* Ensure : performs a deep first search in g from v calling f(v, arg) on
 *    vertex reach. ind indicates the remaining vertices to visit. In order to 
 *    perform a full DFS on g starting on v, ind must be equal to [1..n]\v.
 * Require : v < g->n and validity of g/ind.
 * WARNING : recursive algorithm, may be slow. ind is modified at each call.
 * */
void graph_dfs(graph_p g, ind_p ind, uint v, 
    void(*f)(uint, void*), void* arg);

/* Ensure : return 1 if (g, ind union {0}) is connected, 0 otherwise. 
 * Require : validity of g, ind. 
 * WARNING : based of dfs -> may be slow.
 * */
int graph_is_connected_subgraph(graph_p g, ind_p ind);

/* Ensure : given a set of points from the plane and r a radius, 
 *    returns a graph where an edge between u and v <=> d(u,v) <= r.
 * Require : coord should be an array of size 2n. 
 *    The point xi = (coord[2*i], coord[2*i+1]).
 * WARNING : malloc.
 * */
graph_p graph_from_coord(float* coord, char r, uint n);

/* Ensure : same as graph_from_coord except coord is in the file at path.
 * Require : file at path of the form (%i %f %f\n)* .
 * WARNING : malloc and file opening.
 * */
graph_p graph_from_file(char* path, char r);

/* Ensure : release the memory used by g.
 * */
void graph_free(graph_p g);

void graph_print(graph_p g);

void graph_print_subgraph(graph_p g, ind_p ind);

#endif   /* ----- #ifndef graph_INC  ----- */
