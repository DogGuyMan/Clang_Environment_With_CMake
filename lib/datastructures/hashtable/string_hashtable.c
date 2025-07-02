#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "string_hashtable.h"

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
	memcpy(temp_string_hashtable, &DEFAULT_STRING_HASHTABLE_VTABLE_TEMPLATE, sizeof(StringHashTable));
	int bucket_idx = 0;
	size_t max_idx = sizeof(BUCKET_SIZES)/sizeof(int);

	for(bucket_idx = 0; bucket_idx < max_idx; bucket_idx++) {
		if(capacity <= BUCKET_SIZES[bucket_idx]) { break; }
	}

	temp_string_hashtable->m_bucket_idx = bucket_idx;
	temp_string_hashtable->m_array_ptr = (StringBucket*) malloc(sizeof(StringBucket) * BUCKET_SIZES[temp_string_hashtable->m_bucket_idx]);
	if(temp_string_hashtable->m_array_ptr == NULL) {
		perror("memory allocate failed\n");
		abort();
	}
	for(int i = 0; i < BUCKET_SIZES[temp_string_hashtable->m_bucket_idx]; i++) {
		memcpy((temp_string_hashtable->m_array_ptr + i), &DEFAULT_STRING_BUCKET_VTABLE_TEMPLATE, sizeof(StringBucket));
	}
	return temp_string_hashtable;
}

void DestroyStringHashTable(struct StringHashTable * self_ptr){
	if(self_ptr == NULL) {
		return;
	}
	if(self_ptr->m_array_ptr != NULL) {
		int capacity = BUCKET_SIZES[self_ptr->m_bucket_idx];
		for(int i = 0; i < capacity; i++) {
			StringBucket * cur_bucket = (self_ptr->m_array_ptr + i);
			if(cur_bucket->m_is_occupied)
				free((char*)cur_bucket->m_key);
		}
		free(self_ptr->m_array_ptr);
		self_ptr->m_array_ptr = NULL;
	}

	free(self_ptr);
}

static unsigned StringHashFunction(const char* key) {
	unsigned hash_code = 0;
	char* char_ptr = (char*)key;
	const int fixed_prime = 33;
	while(*char_ptr) {
		hash_code = (hash_code * fixed_prime) + *char_ptr++;
	}
	return hash_code;
}

static unsigned HashFunction(unsigned i, unsigned original_hash_code, unsigned capacity) {
	long long temp_hash_code = original_hash_code;
	long long quad = (i * i);
	temp_hash_code += (quad % capacity);
	return (unsigned)((temp_hash_code + (i*i)) % capacity);
}

// return index, -1 if table is full or error
unsigned StringHashTableFunction (struct StringHashTable * self_ptr, const char* key){
	if(self_ptr == NULL || key == NULL) {
		perror("null pointer error\n");
		abort();
	}
	unsigned capacity = BUCKET_SIZES[self_ptr->m_bucket_idx];
	unsigned original_hash = (StringHashFunction(key) % capacity);
	unsigned hash_code = original_hash;
	int i = 0;

	StringBucket* bucket_ptr = self_ptr->m_array_ptr;

	// Quadratic probing
	while(bucket_ptr[hash_code].m_is_occupied == true && i < capacity) {
		if(strcmp(bucket_ptr[hash_code].m_key, key) == 0) break;
		// ❌ There is a danger of an infinite loop, and it can't iterate through all buckets.
		// hash_code = (((int)(key / 2) + hash_code) % BUCKET_SIZES[self_ptr->m_bucket_idx]);
		// 🚸 Solve Clustering Problems
		// hash_code = (hash_code + 1) % BUCKET_SIZES[self_ptr->m_bucket_idx];
		hash_code = HashFunction(++i, original_hash, capacity);
		if(i >= capacity) return -1; // no more space to assign
	}
	return hash_code;
}

void StringHashTableAdd (struct StringHashTable * self_ptr, const char* key, int value){
	if(self_ptr == NULL || key == NULL) {
		perror("null pointer error\n");
		abort();
	}
	int hash_code = self_ptr->hash(self_ptr, key);
	if(hash_code == -1) {
		perror("Hash Table is Full\n");
		return;
	}
	StringBucket * selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;

	// 기존 키 업데이트인지 새로운 삽입인지 확인
	bool is_update = selected_bucket_ptr->m_is_occupied &&
					 selected_bucket_ptr->m_key != NULL &&
					 strcmp(selected_bucket_ptr->m_key, key) == 0;

	if(!is_update) {
		// 새로운 키 삽입
		if(selected_bucket_ptr->m_key != NULL) {
			free((char *) selected_bucket_ptr->m_key);
		}
		selected_bucket_ptr->m_key = malloc(strlen(key) + 1);
		if(selected_bucket_ptr->m_key == NULL) {
			perror("memory allocation failed\n");
			abort();
		}
		strcpy(selected_bucket_ptr->m_key, key);
		selected_bucket_ptr->m_is_occupied = true;
	}

	// 값 업데이트 (새 삽입이든 기존 키 업데이트든)
	selected_bucket_ptr->m_value = value;
}

bool StringHashTableIsKeyExists (struct StringHashTable * self_ptr, const char* key){
	if(self_ptr == NULL || self_ptr->m_array_ptr == NULL || key == NULL) {
		return false;
	}
	int hash_code = self_ptr->hash(self_ptr, key);
	if(hash_code == -1) {
		return false; // 테이블이 가득 차서 키를 찾을 수 없음
	}
	StringBucket* selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;

	return 	selected_bucket_ptr->m_is_occupied &&
			selected_bucket_ptr->m_key != NULL &&
			strcmp(selected_bucket_ptr->m_key, key) == 0;
}

StringKeyAndValuePair StringHashTableGet (struct StringHashTable * self_ptr, const char* key){
	if(self_ptr == NULL || key == NULL) {
		perror("null pointer error\n");
		return (StringKeyAndValuePair) { .m_key = NULL, .m_value = 0 };
	}

	// 먼저 키가 존재하는지 확인
	if(!self_ptr->is_key_exists(self_ptr, key)) {
		return (StringKeyAndValuePair) { .m_key = NULL, .m_value = 0 };
	}

	int hash_code = self_ptr->hash(self_ptr, key);
	if(hash_code == -1) {
		return (StringKeyAndValuePair) { .m_key = NULL, .m_value = 0 };
	}

	return (StringKeyAndValuePair) {.m_key = (char*)key, .m_value = (self_ptr->m_array_ptr)[hash_code].m_value};

	// StringKeyAndValuePair res;
	// res.m_key = (char*) malloc(strlen(key) + 1); ❌ 메모리 누수 발생! res.m_key에서 get할떄마다 copy가 발생해서 그런듯
	// if(res.m_key == NULL) {
	// 	perror("memory allocation failed\n");
	// 	return (StringKeyAndValuePair) { .m_key = NULL, .m_value = 0 };
	// }
	// strcpy(res.m_key, key);
	// res.m_value = (self_ptr->m_array_ptr)[hash_code].m_value;
	// return res;
}

StringKeyAndValuePair  StringHashTableRemove (struct StringHashTable * self_ptr, const char* key){
	if(self_ptr == NULL) {
		perror("self pointer is null\n");
		abort();
	}
	if(!self_ptr->is_key_exists(self_ptr, key)) {
		return (StringKeyAndValuePair) {.m_key = NULL, .m_value = 0};
	}

	int hash_code = self_ptr->hash(self_ptr, key); // !
		if(hash_code == -1) {
		// Must Scale Up
		perror("Hash Table is Full\n");
		return (StringKeyAndValuePair) { .m_key = NULL, .m_value = 0 };
	}

	StringBucket * selected_bucket_ptr = self_ptr->m_array_ptr + hash_code;
	StringKeyAndValuePair res;
	res.m_key = (char*) malloc(strlen(key) + 1);
	strcpy(res.m_key, selected_bucket_ptr->m_key);
	res.m_value = selected_bucket_ptr->m_value;
	free(selected_bucket_ptr->m_key);
	selected_bucket_ptr->m_key = NULL;
	selected_bucket_ptr->m_value = 0;
	selected_bucket_ptr->m_is_occupied = false;
	return res;
}
