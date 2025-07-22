#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hashtable.h"

static const int BUCKET_SIZES[] =
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

// static const int MIN_PRIME = 53;
static const int MAX_PRIME = 1610612741;

static const Bucket DEFAULT_BUCKET_TEMPLATE = {
	.m_key = -1,
	.m_value = 0,
	.m_is_occupied = false
};

static const HashTable DEFAUT_HASHTABLE_TEMPLATE = {
	.m_array_ptr = NULL,
	.m_bucket_idx = 0,
	.hash = HashTableFunction,
	.add = HashTableAdd,
	.is_key_exists = HashTableIsKeyExists,
	.get = HashTableGet,
	.remove = HashTableRemove
};

HashTable* CreateHashTable(int capacity){
	if(capacity <= 0 || capacity > MAX_PRIME) {
		perror("invalid capacity size\n");
		abort();
	}
	HashTable * temp_hashtable = (HashTable *) malloc(sizeof(HashTable));
	if(temp_hashtable == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	memcpy(temp_hashtable, &DEFAUT_HASHTABLE_TEMPLATE, sizeof(HashTable));
	int bucket_idx = 0;
	size_t max_idx = sizeof(BUCKET_SIZES)/sizeof(int);

	for(bucket_idx = 0; bucket_idx < max_idx; bucket_idx++) {
		if(capacity <= BUCKET_SIZES[bucket_idx]) { break; }
	}

	temp_hashtable->m_bucket_idx = bucket_idx;
	temp_hashtable->m_array_ptr = (Bucket*) malloc(sizeof(Bucket) * BUCKET_SIZES[temp_hashtable->m_bucket_idx]);
	if(temp_hashtable->m_array_ptr == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	for(int i = 0; i < BUCKET_SIZES[temp_hashtable->m_bucket_idx]; i++) {
		memcpy((temp_hashtable->m_array_ptr + i), & DEFAULT_BUCKET_TEMPLATE, sizeof(Bucket));
	}
	return temp_hashtable;
}

void DestroyHashTable(struct HashTable * self_ptr){
	if(self_ptr == NULL) {
		return;
	}
	if(self_ptr->m_array_ptr != NULL) {
		free(self_ptr->m_array_ptr);
		self_ptr->m_array_ptr = NULL;
	}

	free(self_ptr);
	self_ptr = NULL;
}

static unsigned HashFunction(unsigned i, unsigned original_hash_code, unsigned capacity) {
	return (original_hash_code + (i * i)) % capacity;
}
// return index
unsigned  HashTableFunction (struct HashTable * self_ptr, int key){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	unsigned capacity = BUCKET_SIZES[self_ptr->m_bucket_idx];
	unsigned original_hash = (key % capacity);
	unsigned hash_code = original_hash;
	unsigned i = 0;

	Bucket* bucket_ptr = self_ptr->m_array_ptr;

	// Quadratic probing
	while(bucket_ptr[hash_code].m_is_occupied == true && i < capacity) {
		if(bucket_ptr[hash_code].m_key == key) break;
		// ❌ There is a danger of an infinite loop, and it can't iterate through all buckets.
		// hash_code = (((int)(key / 2) + hash_code) % BUCKET_SIZES[self_ptr->m_bucket_idx]);
		// 🚸 Solve Clustering Problems
		// hash_code = (hash_code + 1) % BUCKET_SIZES[self_ptr->m_bucket_idx];
		hash_code = HashFunction(++i, original_hash, capacity);
		if(i >= capacity) return -1; // no more space to assign
	}
	return hash_code;
}

void HashTableAdd (struct HashTable * self_ptr, int key, int value){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	unsigned hash_code = self_ptr->hash(self_ptr, key); // !
	if(hash_code == -1) {
		// Must Scale Up
		perror("Hash Table is Full\n");
		return;
	}
	Bucket * selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;
	selected_bucket_ptr->m_key = key;
	selected_bucket_ptr->m_value = value;
	selected_bucket_ptr->m_is_occupied = true;
}

bool HashTableIsKeyExists (struct HashTable * self_ptr, int key){
	if(self_ptr == NULL || self_ptr->m_array_ptr == NULL) {
		return false;
	}
	unsigned hash_code = self_ptr->hash(self_ptr, key); // !
	if(hash_code == -1) {
		// Must Scale Up
		perror("Hash Table is Full\n");
		return false;
	}
	Bucket* selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;

	return 	selected_bucket_ptr->m_key == key &&
			selected_bucket_ptr->m_is_occupied;
}

KeyAndValuePair  HashTableGet (struct HashTable * self_ptr, int key){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	unsigned hash_code = self_ptr->hash(self_ptr, key); // !
	if(hash_code == -1) {
		// Must Scale Up
		perror("Hash Table is Full\n");
		return (KeyAndValuePair) { .m_key = -1, .m_value = 0 };
	}
	return (KeyAndValuePair) { .m_key = key, .m_value = (self_ptr->m_array_ptr)[hash_code].m_value};
}

KeyAndValuePair  HashTableRemove (struct HashTable * self_ptr, int key){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	if(!self_ptr->is_key_exists(self_ptr, key)) {
		return (KeyAndValuePair) {.m_key = -1, .m_value = 0};
	}

	unsigned hash_code = self_ptr->hash(self_ptr, key); // !
		if(hash_code == -1) {
		// Must Scale Up
		perror("Hash Table is Full\n");
		return (KeyAndValuePair) { .m_key = -1, .m_value = 0 };
	}

	Bucket * selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;
	int res = selected_bucket_ptr->m_value;
	selected_bucket_ptr->m_key = -1;
	selected_bucket_ptr->m_value = 0;
	selected_bucket_ptr->m_is_occupied = false;
	return (KeyAndValuePair) { .m_key = key, .m_value = res };
}
