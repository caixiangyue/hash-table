#include "hash_table.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

static int
is_null(const char *str);

int
main(void)
{
    const char *k1 = "k1";
    const char *v1 = "v1";
    const char *k2 = "k2";
    const char *v2 = "v2";
    const char *v3 = "v3";

    HashTable *ht = hash_table_new();
    hash_table_insert(ht, k1, v1);
    hash_table_insert(ht, k2, v2);
    char *value = hash_table_find(ht, k1);
    assert(strcmp(value, v1) == 0);
    value = hash_table_find(ht, k2);
    assert(strcmp(value, v2) == 0);
    hash_table_insert(ht, k2, v3);
    value = hash_table_find(ht, k2);
    assert(strcmp(value, v3) == 0);
    hash_table_erase(ht, k1);
    value = hash_table_find(ht, k1);
    assert(is_null(value));

    for (int i = 0; i < HASH_TABLE_INITIAL_BASE_SIZE; ++i) {
        char str[25];
        snprintf(str, 7, "test%d", i);
        hash_table_insert(ht, str, str);
    }
    assert(ht->count > HASH_TABLE_INITIAL_BASE_SIZE);
    hash_table_free(ht);
    return 0;
}

static int
is_null(const char *str)
{
    if (str == NULL)
        return true;
    return false;
}
