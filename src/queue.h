/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/10/2020 22:48:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thibaut Milhaud (tm), thibaut.milhaud@ensiie.fr
 *   Organization:  ensiie, univ-tln/Imath
 *
 * =====================================================================================
 */

#ifndef  queue_INC
#define  queue_INC


#include <stdlib.h>
#include <stdio.h>

typedef struct queue{
  unsigned top;
  unsigned bot;
  unsigned n; 
  unsigned* data;
} queue_t;

typedef queue_t* queue_p; 

queue_p queue_new(unsigned n);

void queue_push(queue_p q, unsigned i);

#define QUEUE_CARD(q) q->top - q->bot

unsigned queue_pop_bot(queue_p q);

unsigned queue_pop_top(queue_p q);

void queue_print(queue_p q);

void queue_free(queue_p q);

#endif   /* ----- #ifndef queue_INC  ----- */


