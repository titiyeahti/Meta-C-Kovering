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

/*  TODO test this thing */
void graph_connect(graph_p g, ind_p ind){
  uint* pred;
  uint card, k, i;
  uint* v;
  queue_p in, out;

  IND_CARD(ind, g->n, k, card);

  pred = malloc((g->n)*sizeof(uint));
  for(k=0; k<g->n; k++)
    pred[k] = g->n + 1;

  in = queue_new(card);
  out = queue_new(g->n - card);

  queue_push(out, 0);

  /* ~BFS over the graph until every vertex in ind have been reached 
   *  * the vertices of ind are always explored before those who are not
   */
  while((QUEUE_CARD(in) || QUEUE_CARD(out))
      && card) {
    if (QUEUE_CARD(in))
      k = queue_pop_top(in);
    else 
      k = queue_pop_bot(out);

    FOR_ALL_NEIGH(g, k, v){
      if(pred[*v] != g->n+1){
        if(IND_TEST(ind, *v)){
          queue_push(in, *v);
          card --;
        }
        else
          queue_push(out, *v);

        pred[*v] = k;
      }
    }
  }

  /* connect the different connected part of ind */
  for(k=0; k<g->n; k++){
    if(IND_TEST(ind, k)){
      i = pred[k];
      while(!IND_TEST(ind, i)){
        IND_SET(ind, i); 
        i = pred[i];
      }
    }
  }

  /* need to remove 0 as it have been added during the previous loop */
  IND_UNSET(ind, 0);

  queue_free(in);
  queue_free(out);
}

/* Deep first search */
void graph_dfs(graph_p g, ind_p ind, uint v, 
    void(*f)(uint, void*),void* arg){
  uint* s;
  if (f) (*f)(v, arg);

  FOR_ALL_NEIGH(g, v, s){
    if(IND_TEST(ind, *s)){
      IND_UNSET(ind, *s);
      graph_dfs(g, ind, *s, f, arg);
    }
  }
}

int graph_is_connected_subgraph(graph_p g, ind_p ind){
  uint k, card;
  ind_p to_see;

  to_see = IND_NEW(g->n);
  IND_COPY(to_see, ind, g->n);
  IND_UNSET(to_see, 0);

  graph_dfs(g, to_see, 0, NULL, NULL);

  IND_CARD(to_see, g->n, k, card);

  free(to_see);
  return (card == 0);
}

graph_p graph_from_coord(float* coord, char r, uint n){
  uint* temp;
  graph_p res;
  uint m, i, j, spot;
  float dist2;
  float up = (float)r*r;
  res = graph_new(n);

  /* Counting edges */
  m = 0;
  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      dist2 = COORD_SQRDIST(coord, i, j);
      if (i != j) {
        if (dist2 <= up){
          m++;
        }
      }
    }
  }

  /* Storing edges */
  res->edges = malloc(m*sizeof(uint));
  res->vertices[0] = 0;
  res->vertices[n] = m;
  for(i=0; i<n; i++){
    m = 0;
    spot = res->vertices[i]; 
    for(j=0; j<n; j++){
      dist2 = COORD_SQRDIST(coord, i, j);
      if (i != j) {
        if (dist2 <= up){
          res->edges[spot+m] = j;
          m++;
        }
      }
    }
    res->vertices[i+1] = spot + m;
  }

  return res;
}

graph_p graph_from_file(char* path, char r){
  uint n;
  graph_p res;
  float* coord;

  coord = coord_from_file(path, &n);
  res = graph_from_coord(coord, r, n);
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
      printf("%d ", *s);
    }
    printf("\n");
  }
}

void graph_print_subgraph(graph_p g, ind_p ind){
  uint i;
  uint* s;
  for(i=0; i<g->n; i++){
    if(IND_TEST(ind, i)) {
      printf("%d : ", i);
      FOR_ALL_NEIGH(g, i, s) {
        if(IND_TEST(ind, *s)) {
          printf("%d ", *s);
        }
      }
      printf("\n");
    }
  }
}
