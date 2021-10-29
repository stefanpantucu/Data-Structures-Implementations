#include "list.h"

#ifndef _STACK_
#define _STACK_

typedef struct stack
{
    List top;
} TStack, *Stack;

Stack create_stack();

int push(Stack stack, void *info);
void *pop(Stack stack);
void *top(Stack stack);

int is_empty(Stack stack);
int nr_elem_stack(Stack stack);

int reverse_stack(Stack dest, Stack source);
void print_stack(Stack stack, TPrint print_elem);
int find_in_stack(Stack stack, void *search, TFCmp fcmp);

void reset_s(Stack stack, TFree free_elem);
void delete_s(Stack *stack, TFree free_elem);

#endif