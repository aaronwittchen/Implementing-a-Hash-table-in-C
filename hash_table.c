#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"
#include "prime.h"

#define HT_INITIAL_BASE_SIZE 53
#define HT_PRIME_1 151
#define HT_PRIME_2 163
static ht_item HT_DELETED_ITEM = {NULL, NULL};

/**
 * Creates a new item with the given key and value.
 * 
 * @param k The key for the new item.
 * @param v The value for the new item.
 * @return A pointer to the newly created item.
 */
static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

/**
 * Creates a new hash table with a specified base size.
 * 
 * @param base_size The initial size for the hash table.
 * @return A pointer to the newly created hash table.
 */
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

/**
 * Creates a new hash table with the default initial size.
 * 
 * @return A pointer to the newly created hash table.
 */
ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

/**
 * Deletes an item and frees its memory.
 * 
 * @param i The item to be deleted.
 */
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

/**
 * Deletes the entire hash table and frees its memory.
 * 
 * @param ht The hash table to be deleted.
 */
void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

/**
 * Computes a hash value for a given string using a specified base and modulus.
 * 
 * @param s The string to be hashed.
 * @param a The base to be used in the hash function.
 * @param m The modulus to reduce the hash value.
 * @return The computed hash value.
 */
static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash = (hash * a + s[i]) % m;
    }
    return (int)hash;
}

/**
 * Computes the hash index for a given string with collision handling.
 * 
 * @param s The string to be hashed.
 * @param num_buckets The number of buckets in the hash table.
 * @param attempt The current attempt number for handling collisions.
 * @return The computed index for the hash table.
 */
static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

/**
 * Inserts a new key-value pair into the hash table.
 * If the key already exists, it updates the value.
 * 
 * @param ht The hash table where the item is to be inserted.
 * @param key The key for the item to be inserted.
 * @param value The value for the item to be inserted.
 */
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }

    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;

    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        if (strcmp(cur_item->key, key) == 0) {
            ht_del_item(cur_item);
            ht->items[index] = item;
            return;
        }
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }

    ht->items[index] = item;
    ht->count++;
}

/**
 * Searches for a value by its key in the hash table.
 * 
 * @param ht The hash table to search.
 * @param key The key to search for.
 * @return The value associated with the key, or NULL if not found.
 */
char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM && strcmp(item->key, key) == 0) {
            return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

/**
 * Deletes a key-value pair from the hash table by its key.
 * 
 * @param ht The hash table from which the item is to be deleted.
 * @param key The key of the item to be deleted.
 */
void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM && strcmp(item->key, key) == 0) {
            ht_del_item(item);
            ht->items[index] = &HT_DELETED_ITEM;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }

    ht->count--;

    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
}

/**
 * Resizes the hash table to a new base size.
 * 
 * @param ht The hash table to resize.
 * @param base_size The new base size for the hash table.
 */
static void ht_resize(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }

    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

/**
 * Resizes the hash table up by doubling its base size.
 * 
 * @param ht The hash table to resize.
 */
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

/**
 * Resizes the hash table down by halving its base size.
 * 
 * @param ht The hash table to resize.
 */
static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
