/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/10/2020 22:55:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#include "queue.h"

queue_p new_queue(uint n){
  queue_p ret = malloc(sizeof(queue_p));
  ret->top = 0;
  ret->bot = 0;
  res->n = n;
  ret->data = malloc(n*sizeof(uint));

  return ret;
}

void queue_push(queue_p q, uint i){
  if(q->top < q->n){
    q->data[top] = i;
    q->top ++;
  }
  else {
    printf("queue_push : queue is full\n");
    exit(EXIT_FAILURE);
  }
}

uint queue_pop_bot(queue_p q) {
  uint res;
  
  if(QUEUE_CARD(q)){
    res = q->data[q->bot];
    q->bot ++;
    return res;
  }
  else {
    fprintf(stderr, "queue_pop_bot : queue is empty\n");
    exit(EXIT_FAILURE);
  }
}

uint queue_pop_top(queue_p q) {
  uint res;

  if(QUEUE_CARD(q)){
    q->top --;
    res = q->data[q->top];
  }
  else {
    fprintf(stderr, "queue_pop_top : queue is empty\n");
    exit(EXIT_FAILURE);
  }
}

void queue_print(queue_p q){
  uint i;
  for(i=q->bot; i<q->top; i++)
    printf("%d ", q->data[i]);

  printf("\n");
}

void queue_free(queue_p q){
  free(q->data);
  free(q);
}
