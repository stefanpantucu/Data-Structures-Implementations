#include "hash.h"

// initializes a hash table
THash *init_hash(size_t no_elem, TFHash hash_func)
{
    THash *htable = (THash *)calloc(1, sizeof(THash));
    if (!htable) return NULL; // failed to allocate memory

    // allocate the array of lists
    htable->array = (List *)calloc(no_elem, sizeof(List));
    if (!htable->array) {
        free(htable);
        return NULL;
    }

    htable->no_elem = no_elem;
    htable->hash_func = hash_func;

    return htable;
}

// returns 1 if the searched element is found, 0 otherwise
int find_hash(THash *htable, void *search, TFCmp fcmp)
{
    int code = htable->hash_func(search);

    // the bucket is empty
    if (htable->array[code] == NULL) return 0;

    List list = htable->array[code];

    // use the find function to search the element in the list
    return find(&list, search, fcmp);
}

// ordered insertion in the hash table
int insert_hash(THash *htable, void *info, TFCmp fcmp)
{
    if (find_hash(htable, info, fcmp))
        return 1; // the element is already in the hash table
    
    int code = htable->hash_func(info);
    List list = htable->array[code];

    return insert(&list, info, fcmp);
}

// destroy the hash table
void destroy_hash(THash **htable, TFree free_func)
{
    List *list, el, aux;

    for (list = (*htable)->array; list < (*htable)->array + (*htable)->no_elem; list++) {
        for (el = *list; el != NULL; ) {
            aux = el;
            el = el->next;

            free_func(aux->info);
            free(aux);
        }
    }

    free((*htable)->array);
    free(*htable);
    *htable = NULL;
}

// prints the entire hash table
void print_hash(THash *hash, TPrint print_elem)
{
    for (int i = 0 ; i < hash->no_elem; i++) {
        List list = hash->array[i];
        if (list) {
            printf("List %d:", i);
            print_list(list, print_elem);
            printf("\n");
        }
    }
}