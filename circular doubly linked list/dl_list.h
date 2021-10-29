#include <stdio.h>
#include <stdlib.h>

#ifndef _DOUBLY_LINKED_LIST_WITH_SENTINEL_
#define _DOUBLY_LINKED_LIST_WITH_SENTINEL_

typedef struct node
{
    void *info;
    struct node *next; // pointer to next node
    struct node *prev; // pointer to previous node
} list_node, *TDLL;

typedef void (*TFree)(void *); // free function type
typedef int (*TFCmp)(void*, void*); // compare function type

TDLL init_list();
TDLL alloc_node(void *info);

int push_front(TDLL list, void *info);
int push_back(TDLL list, void *info);
int insert(TDLL list, void *info, TFCmp fcmp);

void reset_list(TDLL list, TFree free_func);
void delete_list(TDLL *list, TFree free_func);

#endif