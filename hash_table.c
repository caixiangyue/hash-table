#include "hash_table.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

static Item DELETED_ITEM = {NULL, NULL};

static Item*
hash_table_item_new(const char *key, const char *value)
{
    Item *item = malloc(sizeof(Item));
    item->key = strdup(key);
    item->value = strdup(value);

    return item;
}

HashTable*
hash_table_new()
{
    HashTable *ht = malloc(sizeof(HashTable));
    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(Item*));

    return ht;
}

static void
hash_table_item_free(Item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void
hash_table_free(HashTable *ht)
{
    for (int i = 0; i < ht->size; ++i) {
        Item *item = ht->items[i];

        if (item != NULL && item != &DELETED_ITEM)
            hash_table_item_free(item);
    }

    free(ht->items);
    free(ht);
}

static inline int
hash_table_hash(const char *str, const int prime, const int mod)
{
    long hash = 0;
    const int len = strlen(str);

    for (int i = 0; i < len ; ++i) {
        hash += (long)pow(prime, len - (i + 1)) * str[i];
        hash %= mod;
    }
    return (int)hash;
}

static inline int
hash_table_get_hash(const char *str, const int buckets, const int attempt)
{
    const int hash_a = hash_table_hash(str, HASH_TABLE_PRIME_A, buckets);
    const int hash_b = hash_table_hash(str, HASH_TABLE_PRIME_B, buckets);

    return (hash_a + (attempt * (hash_b + 1))) % buckets;
}

void
hash_table_insert(HashTable *ht, const char *key, const char *value)
{
    if (key == NULL)
        return;
    Item *item = hash_table_item_new(key, value);
    int index = hash_table_get_hash(key, ht->size, 0);
    Item *current_item = ht->items[index];
    int i = 1;
    while (current_item != NULL && current_item != &DELETED_ITEM) {
        if (strcmp(current_item->key, key) == 0) {
            hash_table_erase(ht, key);
            ht->items[index] = item;
            return;
        }
        index = hash_table_get_hash(key, ht->size, i);
        current_item = ht->items[index];
        ++i;
    }
    ht->items[index] = item;
    ++(ht->count);
}

char*
hash_table_find(HashTable *ht, const char *key)
{
    if (key == NULL)
        return NULL;

    int index = hash_table_get_hash(key, ht->size, 0);
    Item *item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &DELETED_ITEM && strcmp(item->key, key) == 0)
            return item->value;
        index = hash_table_get_hash(key, ht->size, i);
        item = ht->items[index];
        ++i;
    }
    return NULL;
}

void
hash_table_erase(HashTable *ht, const char *key)
{
    if (key == NULL)
        return;

    int index = hash_table_get_hash(key, ht->size, 0);
    Item *item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                hash_table_item_free(item);
                ht->items[index] = &DELETED_ITEM;
                --(ht->count);
                return;
            }
        }
        index = hash_table_get_hash(key, ht->size, i);
        item = ht->items[index];
        ++i;
    }
}
