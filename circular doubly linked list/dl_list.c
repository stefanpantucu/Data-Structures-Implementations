#include "dl_list.h"

// intialize a circular doubly linked list with sentinel
TDLL init_list()
{
    TDLL aux;
    aux = (TDLL)calloc(1, sizeof(list_node));
    if (!aux) return NULL;

    aux->info = NULL;
    aux->next = aux;
    aux->prev = aux;

    return aux;
}

// alocates memory for a doubly linked list's node
TDLL alloc_node(void *info)
{
    TDLL node = (TDLL)calloc(1, sizeof(list_node));
    if (!node) return NULL;

    node->info = info;
    node->next = NULL;
    node->prev = NULL;
}

// inserts info after the sentinel
int push_front(TDLL list, void *info)
{
    TDLL node = alloc_node(info);
    if (!node) return 1; // failure

    node->next = list->next;
    node->prev = list;
    list->next->prev = node;
    list->next = node;

    return 0; // success
}

// inserts info before the sentinel
int push_back(TDLL list, void *info)
{
    TDLL node = alloc_node(info);
    if (!node) return 1; // failure

    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;

    return 0; // success
}

// ordered insertion
int insert(TDLL list, void *info, TFCmp fcmp)
{
    TDLL aux, it = list->next;
    aux = alloc_node(info);
    if (!aux) return 1; // failure

    while (it != list) {
        if (fcmp(info, it->info) < 0) {
            aux->next = it;
            aux->prev = it->prev;
            it->prev->next = aux;
            it->prev = aux;

            return 0; // success
        }

        it = it->next;
    }

    free(aux);
    return push_back(list, info);
}

// empties the list
void reset_list(TDLL list, TFree free_func)
{
    TDLL it = list->next, aux;

    while (it != list) {
        aux = it;
        it = it->next;
        free_func(aux->info);
        free(aux);
    }

    list->next = list->prev = list; // empty list
}

// destroys the entire list
void delete_list(TDLL *list, TFree free_func)
{
    reset_list(*list, free_func);
    free(*list);
    *list = NULL;
}