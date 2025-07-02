#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hashtable.h"

// int main() {
//	int bucket_primes_size = sizeof(BUCKET_SIZES)/sizeof(int);
//	printf("bucket_primes_size : %d\n", bucket_primes_size);
//
//	for(int i = 0; i < bucket_primes_size; i++) {
//		printf("2^%d prime : %u\n", i,  (unsigned int)(log(BUCKET_SIZES[i])/log(2)));
//	}
//	return 0;
// }

static const Bucket DEFAULT_BUCKET_VTABLE_TEMPLATE = {
	.m_key = -1,
	.m_value = 0,
	.m_is_occupied = false
};

static const HashTable DEFAUT_HASHTABLE_VTABLE_TEMPLATE = {
	.m_array_ptr = NULL,
	.m_bucket_idx = 0,
	.hash = HashTableFunction,
	.add = HashTableAdd,
	.is_key_exists = HashTableIsKeyExists,
	.get = HashTableGet,
	.remove = HashTableRemove
};

HashTable* CreateHashTable(int capacity){
	if(capacity <= 0 || capacity >= MAX_PRIME) {
		perror("invalid capacity size\n");
		abort();
	}
	HashTable * temp_hashtable = (HashTable *) malloc(sizeof(HashTable));
	if(temp_hashtable == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	memcpy(temp_hashtable, &DEFAUT_HASHTABLE_VTABLE_TEMPLATE, sizeof(HashTable));
	unsigned int bucket_idx = (unsigned int) log((double)capacity)/log((double)2);
	temp_hashtable->m_bucket_idx = bucket_idx + 1;
	temp_hashtable->m_array_ptr = (Bucket*) malloc(sizeof(Bucket) * BUCKET_SIZES[temp_hashtable->m_bucket_idx]);
	if(temp_hashtable->m_array_ptr == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	for(int i = 0; i < BUCKET_SIZES[temp_hashtable->m_bucket_idx]; i++) {
		memcpy((temp_hashtable->m_array_ptr + i), & DEFAULT_BUCKET_VTABLE_TEMPLATE, sizeof(Bucket));
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

// return index
int  HashTableFunction (struct HashTable * self_ptr, int key){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	int capacity = BUCKET_SIZES[self_ptr->m_bucket_idx];
	int original_hash = (key % capacity);
	int hash_code = original_hash;
	int i = 0;

	Bucket* bucket_ptr = self_ptr->m_array_ptr;

	// Quadratic probing
	while(bucket_ptr[hash_code].m_is_occupied == true && i < capacity) {
		if(bucket_ptr[hash_code].m_key == key) break;
		// ❌ There is a danger of an infinite loop, and it can't iterate through all buckets.
		// hash_code = (((int)(key / 2) + hash_code) % BUCKET_SIZES[self_ptr->m_bucket_idx]);
		// 🚸 Solve Clustering Problems
		// hash_code = (hash_code + 1) % BUCKET_SIZES[self_ptr->m_bucket_idx];
		i++;
		hash_code = (original_hash + i * i) % capacity;
		if(i >= capacity) return -1; // no more space to assign
	}
	return hash_code;
}

void HashTableAdd (struct HashTable * self_ptr, int key, int value){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	int hash_code = self_ptr->hash(self_ptr, key); // !
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
	int hash_code = self_ptr->hash(self_ptr, key); // !
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
	int hash_code = self_ptr->hash(self_ptr, key); // !
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

	int hash_code = self_ptr->hash(self_ptr, key); // !
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
