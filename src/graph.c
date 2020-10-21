/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  20/10/2020 17:54:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, MPRO
 *
 * =====================================================================================
 */

#include "graph.h"

graph_p graph_new(uint n){
  graph_p res = malloc(sizeof(graph_t));
  res->n = n;
  res->vertices = malloc(sizeof(uint)*(n+1));
  res->edges = NULL;

  return res;
}

graph_p graph_subgraph(graph_p g, ind_p ind){
  uint k, i, card, m, cur, spot;
  uint* s;
  uint* new_indices;
  graph_p res;

  IND_CARD(ind, g->n, k, card);
  res = graph_new(card);
  new_indices = malloc(card*sizeof(uint));

  /* Counting the edges in the subgraph;
   * Replacing the indices of the vertices*/
  cur = 0;
  for(k=0; k<g->n; k++){
    if(IND_TEST(ind, k)){
      new_indices[cur] = k;
      cur ++;
      FOR_ALL_NEIGH(g, i, s){
        if(IND_TEST(ind, *s))
          m++;
      }
    }
  }

  res->edges = malloc(m*sizeof(uint));

  /* Building res->edges & res->vertices */
  for(k=0; k<g->n; k++){
    if(IND_TEST(ind, k)){
      cur = new_indices[k];
      m = 0;
      spot = res->vertices[cur];
      FOR_ALL_NEIGH(g, i, s){
        if(IND_TEST(ind, *s)){
          res->edges[spot+m] = new_indices[*s];
          m++;
        }
      }
      res->vertices[cur+1] = spot + m;
    }
  }

  return res;
}

/* Deep first search */
void graph_dfs(graph_p g, ind_p ind, uint v, void(*f)(uint u)){
  uint* s;
  if (f) (*f)(v);

  FOR_ALL_NEIGH(g, v, s){
    if(IND_TEST(ind, *s)){
      IND_UNSET(ind, *s);
      graph_dfs(g, ind, *s, f);
    }
  }
}

int graph_is_connected_subgraph(graph_p g, int_p ind){
  uint k, card;
  ind_p to_see;

  to_see = IND_NEW(g->n);
  IND_OR(to_see, to_see, ind, g->n, k);
  
  /* TODO : the first vertex should always be in the subgraphs,
   * but who knows... be careful*/
  graph_dfs(g, to_see, 0, NULL);

  IND_CARD(to_see, g->n, k, card);

  return (card == 0);
}

graph_p graph_from_coord(float* coord, uchar r, uint n){
  uint* temp;
  graph_p res;
  uint m, i, j, spot;
  uint ci, cj;
  float dx, dy;
  float up = (float)r*r;
  res = new_graph(n);

  m = 0;
  for(i=0; i<n i++){
    ci = 2*i;
    for(j=0; j<n; j++){
      cj = 2*j;

      if (i != j) {
        dx = coord[ci] - coord[cj];
        dy = coord[ci+1] - coord[cj+1];
        if (dx*dx + dy*dy <= up){
          m++;
        }
      }
    }
  }

  res->egdes = malloc(m*sizeof(uint));
  res->vertices[0] = 0;
  res->vertices[n] = m;
  for(i=0; i<n i++){
    ci = 2*i;
    m = 0;
    spot = res->vertices[i]; 
    for(j=0; j<n; j++){
      cj = 2*j;

      if (i != j) {
        dx = coord[ci] - coord[cj];
        dy = coord[ci+1] - coord[cj+1];
        if (dx*dx + dy*dy <= up){
          res->edges[spot+m] = j;
          m++;
        }
      }
    }
    res->vertices[i+1] = spot + m;
  }

  return res;
}

void graph_free(graph_p g){
  free(g->vertices);
  free(g->edges);
  free(g);
}

void graph_print(graph_p g){
  uint i;
  uint* s;
  for(i=0; i<g->n; i++){
    printf("%d : ", i);
    FOR_ALL_NEIGH(g, i, s){
      prtinf("%d ", *s);
    }
    printf("\n");
  }
}

