#ifndef __HEADER_GUARD_HASHTABLE__
#define __HEADER_GUARD_HASHTABLE__

#define MAX_CAPACITY

#include <stdbool.h>
// https://planetmath.org/goodhashtableprimes

const int BUCKET_SIZES[] =
{
    // 1
    53,
    // 2^(1~5)
    53, 53, 53, 53, 53,
    // 2^(6~10)
    97, 193, 389, 769, 1543,
    // 2^(11~15)
    3079, 6151, 12289, 24593, 49157,
    // 2^(16~20)
    98317, 196613, 393241, 786433, 1572869,
    // 2^(21~25)
    3145739, 6291469, 12582917, 25165843, 50331653,
    // 2^(26~30)
    100663319, 201326611, 402653189, 805306457, 1610612741,
};

const int DEFAULT_PRIME = BUCKET_SIZES[0];

typedef struct HashTable HashTable;
typedef struct Bucket Bucket;

struct Bucket {
	int m_value;
	bool m_is_occupied;
};

struct HashTable {
	Bucket * m_array_ptr;
	int m_bucket_idx;

	int  (* const hash) (struct HashTable * self_ptr, int key);
	void  (* const add) (struct HashTable * self_ptr, int key, int value);
	bool (* const is_key_exists) (struct HashTable * self_ptr, int key);
	int  (* const get) (struct HashTable * self_ptr, int key);
	int  (* const remove) (struct HashTable * self_ptr, int key);
};

HashTable* CreateHashTable(int capacity);
void DestroyHashTable(struct HashTable * self_ptr);
int  HashTableFunction (struct HashTable * self_ptr, int key);
void HashTableAdd (struct HashTable * self_ptr, int key, int value);
bool HashTableIsKeyExists (struct HashTable * self_ptr, int key);
int  HashTableGet (struct HashTable * self_ptr, int key);
int  HashTableRemove (struct HashTable * self_ptr, int key);


#endif//__HEADER_GUARD_HASHTABLE__
