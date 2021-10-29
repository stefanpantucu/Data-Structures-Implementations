#include "list.h"

// alocates memory for a list's node and puts info as the node's info
List alloc_node(void *info)
{
    List aux;

    aux = (List)calloc(1, sizeof(list_node));
    if (!aux) return NULL;

    aux->info = info;
    aux->next = NULL;

    return aux;
}

// inserts an element at the start of the list
int push_front(List *list, void *info)
{
    List aux = alloc_node(info);
    if (!aux) return 1; // failure

    aux->next = *list;
    *list = aux;

    return 0; // success
}

// inserts an element at the end of the list
int push_back(List *list, void *info)
{
    List aux = alloc_node(info);
    if (!aux) return 1; // failure

    List iterator = *list;
    for (; iterator->next != NULL; iterator = iterator->next) ;

    iterator->next = aux;
    return 0; // success
}

// extracts the element from the start of the list
void *pop_front(List *list)
{
    if (*list == NULL)
        return NULL; // list is empty

    List aux = *list;
    *list = (*list)->next;

    void *info = aux->info;
    free(aux);

    return info;
}

// extracts the element at the end of the list and returns it's info
void *pop_back(List *list)
{
    if (*list == NULL)
        return NULL; // list is empty
    
    void *info;

    // if list has only one element
    if ((*list)->next == NULL) {
        info = pop_front(list);
        return info;
    }

    List iterator = *list;

    for (; iterator->next != NULL; iterator = iterator->next) ;

    info = iterator->next->info;
    free(iterator->next); // free the last node

    return info;
}

// ordered insertion
int insert(List *list, void *info, TFCmp fcmp)
{
    List iterator = *list, prev = NULL;
    List aux = alloc_node(info);
    if (!aux) return 1; // failure

    for (; iterator != NULL; prev = iterator, iterator = iterator->next) {
        if (fcmp(info, iterator->info) < 0) {
            if (prev == NULL) { // info will become the first element
                push_front(list, info);

                free(aux);
                return 0;
            }

            prev->next = aux;
            aux->next = iterator;
            
            return 0;
        }
    }

    if (iterator == NULL) {
        push_back(list, info); // the new element is inserted at the end of the list
        free(aux);
    }

    return 0;
}

// prints the entire list using a specific print function for the elements
void print_list(List list, TPrint print_elem)
{
    for (; list != NULL; list = list->next)
        print_elem(list->info);
}

// returns the number of elements in a list
int no_elements(List list)
{
    int count = 0;
    List iterator = list;

    for (; iterator != NULL; iterator = iterator->next)
        count++;
    
    return count;
}

// returns 1 if the searched element is found, 0 otherwise
int find(List *list, void *search, TFCmp fcmp)
{
    List it = *list;
    for (; it != NULL; it = it->next)
        if (fcmp(it->info, search) == 0){
            return 1; // searched element is found
        }

    return 0; // not found
}

// remove element inside the list and return its info
void *remove_elem(List *list, void *info, TFCmp fcmp)
{
    List iterator = *list, prev = NULL;

    for (; iterator != NULL; prev = iterator, iterator =  iterator->next) {
        if (fcmp(info, iterator->info) == 0) {
            prev->next = iterator->next;
            free(iterator);

            break;
        }
    }

    return info;
}

// deletes the entire list
void delete_list(List *list, TFree free_func)
{
    while (*list) {
        void *info = pop_front(list); // uses pop_front to delete the nodes
        free_func(info);
    }
}
