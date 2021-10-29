#include "list.h"

#ifndef _QUEUE_
#define _QUEUE_

typedef struct queue
{
    List front, rear; // front is the first node and rear is the last one
} TQueue, *Queue;


Queue create_queue();
int insert_q(Queue queue, void *elem);
void *extract_q(Queue queue);
void print_q(Queue queue,  TPrint print_elem);

int nr_elem_q(Queue queue);
int find_in_q(Queue queue, void *search, TFCmp fcmp);
int empty_queue(Queue queue);

void invert(Queue *queue);
void reset_q(Queue queue, TFree free_elem);
void delete_q(Queue *queue, TFree free_elem);

#endif