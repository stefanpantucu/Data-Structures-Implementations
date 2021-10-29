#include <stdio.h>
#include <stdlib.h>

#ifndef _SINGLY_LINKED_LIST_
#define _SINGLY_LINKED_LIST_

typedef struct node
{
    void *info;
    struct node *next;
} list_node, *List;

List alloc_node(void *info);

typedef int (*TFCmp)(void *, void *); // comparison function type
typedef void (*TFree)(void *); // free function type
typedef void (*TPrint)(void *); // print function type

int push_front(List *list, void *info);
int push_back(List *list, void *info);
int insert(List *list, void *info, TFCmp fcmp);

void *pop_front(List *list);
void *pop_back(List *list);
void *remove_elem(List *list, void *info, TFCmp fcmp);

void print_list(List list, TPrint print_elem);
int no_elements(List list);
int find(List *list, void *search, TFCmp fcmp);
void delete_list(List *list, TFree free_func);

#endif