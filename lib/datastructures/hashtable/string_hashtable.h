#ifndef __HEADER_GUARD_STRING_HASHTABLE__
#define __HEADER_GUARD_STRING_HASHTABLE__

#define MAX_CAPACITY

#include <stdbool.h>
#include "hashtable.h"

typedef struct StringHashTable StringHashTable;
struct StringHashTable {
	Bucket * m_array_ptr;
	int m_bucket_idx;

	int  (* const hash) (struct StringHashTable * self_ptr, const char* key);
	void (* const add) (struct StringHashTable * self_ptr, const char* key, int value);
	bool (* const is_key_exists) (struct StringHashTable * self_ptr, const char* key);
	int  (* const get) (struct StringHashTable * self_ptr, const char* key);
	int  (* const remove) (struct StringHashTable * self_ptr, const char* key);
};

StringHashTable* CreateStringHashTable(int capacity);
void DestroyStringHashTable(struct StringHashTable * self_ptr);
int  StringHashTableFunction (struct StringHashTable * self_ptr, const char* key);
void StringHashTableAdd (struct StringHashTable * self_ptr, const char* key, int value);
bool StringHashTableIsKeyExists (struct StringHashTable * self_ptr, const char* key);
KeyAndValuePair  StringHashTableGet (struct StringHashTable * self_ptr, const char* key);
KeyAndValuePair  StringHashTableRemove (struct StringHashTable * self_ptr, const char* key);

const StringHashTable DEFAUT_STRING_HASHTABLE_VTABLE_TEMPLATE = {
	.m_array_ptr = NULL,
	.m_bucket_idx = 0,
	.hash = StringHashTableFunction,
	.add = StringHashTableAdd,
	.is_key_exists = StringHashTableIsKeyExists,
	.get = StringHashTableGet,
	.remove = StringHashTableRemove
};

#endif//__HEADER_GUARD_STRING_HASHTABLE__
