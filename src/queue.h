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

#include "utils.h"

typedef struct queue{
  uint top;
  uint bot;
  uint n; 
  uint* data;
} queue_t;

typedef queue_t* queue_p; 

queue_p queue_new(uint n);

void queue_push(queue_p q, uint i);

#define QUEUE_CARD(q) q->top - q->bot

uint queue_pop_bot(queue_p q);

uint queue_pop_top(queue_p q);

void queue_print(queue_p q);

void queue_free(queue_p q);

#endif   /* ----- #ifndef queue_INC  ----- */


