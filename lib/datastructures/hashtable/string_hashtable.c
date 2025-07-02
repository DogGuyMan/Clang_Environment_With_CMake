#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "string_hashtable.h"

StringHashTable* CreateStringHashTable(int capacity){
	if(capacity <= 0 || capacity > MAX_PRIME) {
		perror("invalid capacity size\n");
		abort();
	}
	StringHashTable * temp_string_hashtable = (StringHashTable *) malloc(sizeof(StringHashTable));
	if(temp_string_hashtable == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	memcpy(temp_string_hashtable, &DEFAUT_STRING_HASHTABLE_VTABLE_TEMPLATE, sizeof(StringHashTable));
	int bucket_idx = 0;
	size_t max_idx = sizeof(BUCKET_SIZES)/sizeof(int);

	for(bucket_idx; bucket_idx < max_idx; bucket_idx++) {
		if(capacity <= BUCKET_SIZES[bucket_idx]) { break; }
	}

	temp_string_hashtable->m_bucket_idx = bucket_idx;
	temp_string_hashtable->m_array_ptr = (Bucket*) malloc(sizeof(Bucket) * BUCKET_SIZES[temp_string_hashtable->m_bucket_idx]);
	if(temp_string_hashtable->m_array_ptr == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	for(int i = 0; i < BUCKET_SIZES[temp_string_hashtable->m_bucket_idx]; i++) {
		memcpy((temp_string_hashtable->m_array_ptr + i), &DEFAULT_BUCKET_VTABLE_TEMPLATE, sizeof(Bucket));
	}
	return temp_string_hashtable;
}

void DestroyStringHashTable(struct StringHashTable * self_ptr){
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

static int StringHashFunction(const char* key) {
	unsigned hash_code = 0;
	unsigned char* char_ptr = key;
	const fixed_prime = 33;
	while(*char_ptr) {
		hash_code = (hash_code * fixed_prime) + *char_ptr++;
	}
	return hash_code;
}

static int HashFunction(unsigned i, unsigned original_hash_code, unsigned capacity) {
	long long temp_hash_code = original_hash_code;
	long long quad = (i * i);
	temp_hash_code += (quad % capacity);
	return temp_hash_code % capacity;
}

// return index
int  StringHashTableFunction (struct StringHashTable * self_ptr, const char* key){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	int capacity = BUCKET_SIZES[self_ptr->m_bucket_idx];
	int original_hash = (StringHashFunction(key) % capacity);
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
		hash_code = HashFunction(++i, original_hash, capacity);
		if(i >= capacity) return -1; // no more space to assign
	}
	return hash_code;
}

void StringHashTableAdd (struct StringHashTable * self_ptr, int key, int value){
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

bool StringHashTableIsKeyExists (struct StringHashTable * self_ptr, const char* key){
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

KeyAndValuePair  StringHashTableGet (struct StringHashTable * self_ptr, const char* key){
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

KeyAndValuePair  StringHashTableRemove (struct StringHashTable * self_ptr, const char* key){
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
