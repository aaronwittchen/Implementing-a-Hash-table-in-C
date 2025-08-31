// Definition of an item
typedef struct {
    char* key;
    char* value;
} ht_item;

// Definition of a hash table
typedef struct {
    int size;
    int base_size;
    int count;
    ht_item** items;
} ht_hash_table;

// Function prototypes
// Important due to the "implicit declaration of function" errors
static ht_item* ht_new_item(const char* k, const char* v);
ht_hash_table* ht_new();
static ht_hash_table* ht_new_sized(const int base_size);
static void ht_resize(ht_hash_table* ht, const int base_size);
static void ht_resize_up(ht_hash_table* ht);
static void ht_resize_down(ht_hash_table* ht);
static void ht_del_item(ht_item* i);
void ht_del_hash_table(ht_hash_table* ht);
static int ht_hash(const char* s, const int a, const int m);
static int ht_get_hash(const char* s, const int num_buckets, const int attempt);
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);

// Utility functions
int ht_size(ht_hash_table* ht);
int ht_is_empty(ht_hash_table* ht);
double ht_load_factor(ht_hash_table* ht);
int ht_contains(ht_hash_table* ht, const char* key);
