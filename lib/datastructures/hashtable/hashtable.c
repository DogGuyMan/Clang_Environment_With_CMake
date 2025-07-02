#include <error.h>
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
	.m_value = 0,
	.m_is_occupied = true
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
	if(capacity <=0) {
		perror("invalid capacity size zero\n");
		abort();
	}
	HashTable * temp_hashtable = (HashTable *) malloc(sizeof(HashTable));
	if(temp_hashtable == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	memcpy(temp_hashtable, &DEFAUT_HASHTABLE_VTABLE_TEMPLATE, sizeof(HashTable));
	unsigned int bucket_size_prime = (unsigned int) log((double)capacity)/log((double)2);
	temp_hashtable->m_bucket_idx = bucket_size_prime;
	temp_hashtable->m_array_ptr = (Bucket*) malloc(sizeof(Bucket) * BUCKET_SIZES[bucket_size_prime]);
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
		perror("self pointer is null\n");
		abort();
	}
	if(self_ptr->m_array_ptr != NULL) {
		free(self_ptr->m_array_ptr);
	}
	free(self_ptr);
}

// return index
int  HashTableFunction (struct HashTable * self_ptr, int key) {
	int hash_code = (key % BUCKET_SIZES[self_ptr->m_bucket_idx]);
	Bucket* bucket_ptr = self_ptr->m_array_ptr;
       	if(bucket_ptr[hash_code].m_is_ocuupied == true) {
		return HashTableFunction(self_ptr, (int)(key / 2) + hash_code);
	}
	return hash_code;
}

void HashTableAdd (struct HashTable * self_ptr, int key, int value){
	int hash_code = self_ptr->hash(self_ptr, key);
	Bucket * selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;
	selected_bucket_ptr->m_value = value;
	selected_bucket_ptr->m_is_occupied = true;
}
bool HashTableIsKeyExists (struct HashTable * self_ptr, int key){return false;}
int  HashTableGet (struct HashTable * self_ptr, int key){return -1;}
int  HashTableRemove (struct HashTable * self_ptr, int key){return -1;}
