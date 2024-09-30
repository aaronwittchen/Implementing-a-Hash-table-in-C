# Implementing a Hash table in C

This project implements a hash table in C, following the tutorial written by [James Routley](https://twitter.com/james_routley)

## Contents

- Setting Up the Hash Table: Define the structures for the hash table and the items it contains.
- Hash Functions:
  - Compute a hash value for a given key.
  - Compute the hash index for inserting and searching items.
- Hash Table Operations:
  - Insert: Add key-value pairs to the hash table.
  - Search: Retrieve the value associated with a given key.
  - Delete: Remove key-value pairs from the hash table.
- Memory Management:
  - Free memory allocated for individual items.
  - Free all memory associated with the hash table and its items.
- Dynamic Resizing: Implement functions for increasing (ht_resize_up) and decreasing (ht_resize_down) the size of the hash table.
- Main Function: Demonstrate the functionality of this hash table implementation.

## Compile and Run

- To compile and run the program, navigate to the file location and use the following commands:
```bash
gcc -o hash_table_program main.c hash_table.c prime.c -lm
./hash_table_program
```

## Appendix

This implementation is not simply copy-and-paste. Several issues have been addressed, including potential overflow in the ht_hash() function, improved memory management in ht_delete(), elimination of duplicate entries in ht_insert(), and enhanced resizing functions.
