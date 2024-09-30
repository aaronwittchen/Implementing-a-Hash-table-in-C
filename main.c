#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main() {
    // Create a new hash table
    ht_hash_table* ht = ht_new();

    printf("1. Create a new hash table\n");
    printf("2. Let's add Name, Age, Occupation, and Country with the following values:\n");
    printf("   John, 30, Software Engineer, USA\n\n");

    // Insert some key-value pairs
    ht_insert(ht, "name", "John");
    ht_insert(ht, "age", "30");
    ht_insert(ht, "occupation", "Software Engineer");
    ht_insert(ht, "country", "USA");

    // Search for existing keys
    char* name = ht_search(ht, "name");
    char* age = ht_search(ht, "age");
    char* occupation = ht_search(ht, "occupation");
    char* country = ht_search(ht, "country");

    // Display searched values
    if (name) 
        printf("Name: %s\n", name);
    if (age) 
        printf("Age: %s\n", age);
    if (occupation) 
        printf("Occupation: %s\n", occupation);
    if (country) 
        printf("Country: %s\n\n", country);

    printf("Let's search for City, which we know was never added to the hash table:\n");

    // Search for a key that doesn't exist
    char* city = ht_search(ht, "city");
    if (city == NULL) {
        printf("City: Not found in hash table\n");
    }

    // Delete an existing key
    printf("\nDeleting 'age'...\n");
    ht_delete(ht, "age");

    // Try searching for the deleted key
    age = ht_search(ht, "age");
    if (age == NULL) {
        printf("Age: Not found in hash table (deleted)\n\n");
    }

    // Insert more items to demonstrate resizing
    printf("Let's add more items:\n");
    printf("City, Language, Food, Sport\n");
    printf("New York, English, Pizza, Soccer\n");
    
    ht_insert(ht, "city", "New York");
    ht_insert(ht, "language", "English");
    ht_insert(ht, "food", "Pizza");
    ht_insert(ht, "sport", "Soccer");

    // Display newly inserted items
    printf("\nNewly inserted items:\n");
    char* city_after = ht_search(ht, "city");
    char* language = ht_search(ht, "language");
    char* food = ht_search(ht, "food");
    char* sport = ht_search(ht, "sport");

    if (city_after) 
        printf("City: %s\n", city_after);
    if (language) 
        printf("Language: %s\n", language);
    if (food) 
        printf("Food: %s\n", food);
    if (sport) 
        printf("Sport: %s\n\n", sport);

    // Cleanup hash table
    ht_del_hash_table(ht);

    printf("Time Complexity:\n");
    printf(" - Insert: O(1) on average, O(n) in the worst case (due to collisions and resizing).\n");
    printf(" - Lookup: O(1) on average, O(n) in the worst case (due to collisions).\n");
    printf(" - Delete: O(1) on average, O(n) in the worst case (due to collisions).\n\n");

    printf("Space Complexity:\n");
    printf(" - O(n) for storing n items in the hash table.\n");

    return 0;
}
