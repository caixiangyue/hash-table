#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_TABLE_PRIME_A 161
#define HASH_TABLE_PRIME_B 171

typedef struct {
    char *key;
    char *value;
} Item;

typedef struct {
    int size;
    int count;
    Item **items;
} HashTable;


HashTable*
hash_table_new();

void
hash_table_free(HashTable *ht);

void
hash_table_insert(HashTable *ht, const char *key, const char *value);

char*
hash_table_find(HashTable *ht, const char *key);

void
hash_table_erase(HashTable *ht, const char *key);

#endif // HASH_TABLE_H
