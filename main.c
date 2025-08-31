#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main() {
    // Create a new hash table
    ht_hash_table* ht = ht_new();
    if (ht == NULL) {
        printf("Failed to create hash table\n");
        return 1;
    }

    printf("=== Hash Table Implementation Demo ===\n\n");
    
    printf("1. Initial state:\n");
    printf("   Size: %d items\n", ht_size(ht));
    printf("   Empty: %s\n", ht_is_empty(ht) ? "Yes" : "No");
    printf("   Load factor: %.2f%%\n\n", ht_load_factor(ht));

    printf("2. Adding key-value pairs:\n");
    printf("   name -> John\n");
    printf("   age -> 30\n");
    printf("   occupation -> Software Engineer\n");
    printf("   country -> USA\n\n");

    // Insert some key-value pairs
    ht_insert(ht, "name", "John");
    ht_insert(ht, "age", "30");
    ht_insert(ht, "occupation", "Software Engineer");
    ht_insert(ht, "country", "USA");

    printf("3. After insertion:\n");
    printf("   Size: %d items\n", ht_size(ht));
    printf("   Load factor: %.2f%%\n\n", ht_load_factor(ht));

    // Search for existing keys
    printf("4. Searching for values:\n");
    char* name = ht_search(ht, "name");
    char* age = ht_search(ht, "age");
    char* occupation = ht_search(ht, "occupation");
    char* country = ht_search(ht, "country");

    if (name) printf("   name: %s\n", name);
    if (age) printf("   age: %s\n", age);
    if (occupation) printf("   occupation: %s\n", occupation);
    if (country) printf("   country: %s\n\n", country);

    printf("5. Testing contains() function:\n");
    printf("   Contains 'name': %s\n", ht_contains(ht, "name") ? "Yes" : "No");
    printf("   Contains 'city': %s\n", ht_contains(ht, "city") ? "Yes" : "No\n");

    // Test null pointer handling
    printf("6. Testing null pointer safety:\n");
    ht_insert(NULL, "test", "value");  // Should not crash
    ht_search(NULL, "test");           // Should return NULL
    ht_delete(NULL, "test");           // Should not crash
    printf("   Null pointer tests completed safely\n\n");

    // Delete an existing key
    printf("7. Deleting 'age'...\n");
    ht_delete(ht, "age");

    printf("   Size after deletion: %d items\n", ht_size(ht));
    printf("   Contains 'age': %s\n", ht_contains(ht, "age") ? "Yes" : "No\n");

    // Insert more items to demonstrate resizing
    printf("8. Adding more items to trigger resize:\n");
    for (int i = 0; i < 20; i++) {
        char key[32], value[32];
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        ht_insert(ht, key, value);
    }
    
    printf("   Final size: %d items\n", ht_size(ht));
    printf("   Final load factor: %.2f%%\n\n", ht_load_factor(ht));

    // Cleanup hash table
    ht_del_hash_table(ht);

    printf("=== Performance Characteristics ===\n");
    printf("Time Complexity:\n");
    printf(" - Insert: O(1) average, O(n) worst case\n");
    printf(" - Lookup: O(1) average, O(n) worst case\n");
    printf(" - Delete: O(1) average, O(n) worst case\n\n");

    printf("Space Complexity: O(n)\n\n");

    printf("=== Improvements Made ===\n");
    printf("✓ Fixed critical bug in delete function\n");
    printf("✓ Added null pointer safety checks\n");
    printf("✓ Improved hash function to prevent overflow\n");
    printf("✓ Added utility functions (size, isEmpty, loadFactor, contains)\n");
    printf("✓ Added configurable load factor constants\n");
    printf("✓ Enhanced error handling and safety\n");

    return 0;
}
