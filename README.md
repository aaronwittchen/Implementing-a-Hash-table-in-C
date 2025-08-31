# Hash Table Implementation in C

A robust, dynamically-resizing hash table implementation in C with collision handling using double hashing.

## Features

- **Dynamic Resizing**: Automatically grows and shrinks based on load factor
- **Collision Resolution**: Uses double hashing for efficient collision handling
- **Memory Safety**: Comprehensive null pointer checks and memory management
- **Utility Functions**: Helper functions for common operations
- **Configurable**: Adjustable load factor thresholds

## API Reference

### Core Functions

```c
// Create and destroy
ht_hash_table* ht_new();
void ht_del_hash_table(ht_hash_table* ht);

// Basic operations
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);

// Utility functions
int ht_size(ht_hash_table* ht);
int ht_is_empty(ht_hash_table* ht);
double ht_load_factor(ht_hash_table* ht);
int ht_contains(ht_hash_table* ht, const char* key);
```

### Usage Example

```c
#include "hash_table.h"
#include <stdio.h>

int main() {
    // Create a new hash table
    ht_hash_table* ht = ht_new();
    
    // Insert key-value pairs
    ht_insert(ht, "name", "John Doe");
    ht_insert(ht, "age", "30");
    ht_insert(ht, "city", "New York");
    
    // Search for values
    char* name = ht_search(ht, "name");
    if (name) {
        printf("Name: %s\n", name);
    }
    
    // Check if key exists
    if (ht_contains(ht, "age")) {
        printf("Age key exists\n");
    }
    
    // Get table statistics
    printf("Size: %d items\n", ht_size(ht));
    printf("Load factor: %.2f%%\n", ht_load_factor(ht));
    
    // Delete an item
    ht_delete(ht, "age");
    
    // Clean up
    ht_del_hash_table(ht);
    return 0;
}
```

## Performance Characteristics

- **Time Complexity**:
  - Insert: O(1) average, O(n) worst case
  - Lookup: O(1) average, O(n) worst case
  - Delete: O(1) average, O(n) worst case
- **Space Complexity**: O(n)

## Implementation Details

### Hash Function
Uses a polynomial rolling hash function with two different prime bases for double hashing:
- Base 1: 151
- Base 2: 163

### Collision Resolution
Implements double hashing with the formula:
```
hash = (hash_a + attempt * (hash_b + 1)) % table_size
```

### Dynamic Resizing
- **Grow**: When load factor > 70%
- **Shrink**: When load factor < 10%
- Resize factor: 2x (double/halve)

### Memory Management
- Automatic memory allocation/deallocation
- Tombstone deletion for efficient removal
- Comprehensive null pointer checks

## Compilation

```bash
gcc -o hashtable main.c hash_table.c prime.c -lm
```

## Testing

Run the demo program:
```bash
./hashtable
```

## Future Enhancements

- Iterator functionality for traversing all key-value pairs
- Support for different data types (not just strings)
- Thread-safe operations
- Custom hash function support
- Performance benchmarking tools
- Explanations