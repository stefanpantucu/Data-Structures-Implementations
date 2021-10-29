#include "list.h"

#ifndef _HASH_TABLE_
#define _HASH_TABLE_

typedef int (*TFHash)(void *); // hash function type

typedef struct
{
    size_t no_elem; // number of buckets in the hash table
    TFHash hash_func; // hash function
    List *array; // array of lists
} THash;

THash *init_hash(size_t no_elem, TFHash hash_func);
int find_hash(THash *htable, void *search, TFCmp fcmp);

int insert_hash(THash *htable, void *info, TFCmp fcmp);
void print_hash(THash *hash, TPrint print_elem);

void destroy_hash(THash **htable, TFree free_func);
#endif