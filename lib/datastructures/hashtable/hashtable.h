#ifndef __HEADER_GUARD_HASHTABLE__
#define __HEADER_GUARD_HASHTABLE__

#define MAX_CAPACITY

#include <stdlib.h>
#include <stdbool.h>
// https://planetmath.org/goodhashtableprimes

typedef struct HashTable HashTable;
typedef struct Bucket Bucket;
typedef struct KeyAndValuePair KeyAndValuePair;

struct KeyAndValuePair {
    int m_key;
    int m_value;
};

struct Bucket {
	int m_key;
	int m_value;
	bool m_is_occupied;
};

struct HashTable {
	Bucket * m_array_ptr;
	int m_bucket_idx;

	unsigned  (* const hash) (struct HashTable * self_ptr, int key);
	void (* const add) (struct HashTable * self_ptr, int key, int value);
	bool (* const is_key_exists) (struct HashTable * self_ptr, int key);
	KeyAndValuePair (* const get) (struct HashTable * self_ptr, int key);
	KeyAndValuePair (* const remove) (struct HashTable * self_ptr, int key);
};

HashTable* CreateHashTable(int capacity);
void DestroyHashTable(struct HashTable * self_ptr);
unsigned  HashTableFunction (struct HashTable * self_ptr, int key);
void HashTableAdd (struct HashTable * self_ptr, int key, int value);
bool HashTableIsKeyExists (struct HashTable * self_ptr, int key);
KeyAndValuePair  HashTableGet (struct HashTable * self_ptr, int key);
KeyAndValuePair  HashTableRemove (struct HashTable * self_ptr, int key);

#endif//__HEADER_GUARD_HASHTABLE__
