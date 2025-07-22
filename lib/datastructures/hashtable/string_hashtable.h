#ifndef __HEADER_GUARD_STRING_HASHTABLE__
#define __HEADER_GUARD_STRING_HASHTABLE__

#define MAX_CAPACITY

#include <stdlib.h>
#include <stdbool.h>

typedef struct StringHashTable StringHashTable;
typedef struct StringBucket StringBucket;
typedef struct StringKeyAndValuePair StringKeyAndValuePair;

struct StringKeyAndValuePair {
    char* m_key;
    int m_value;
};

struct StringBucket
{
	char* m_key;
	int m_value;
	bool m_is_occupied;
};

struct StringHashTable {
	StringBucket * m_array_ptr;
	int m_bucket_idx;

	unsigned  (* const hash) (struct StringHashTable * self_ptr, const char* key);
	void (* const add) (struct StringHashTable * self_ptr, const char* key, int value);
	bool (* const is_key_exists) (struct StringHashTable * self_ptr, const char* key);
	StringKeyAndValuePair (* const get) (struct StringHashTable * self_ptr, const char* key);
	StringKeyAndValuePair (* const remove) (struct StringHashTable * self_ptr, const char* key);
};

StringHashTable* CreateStringHashTable(int capacity);
void DestroyStringHashTable(struct StringHashTable * self_ptr);
unsigned StringHashTableFunction (struct StringHashTable * self_ptr, const char* key);
void StringHashTableAdd (struct StringHashTable * self_ptr, const char* key, int value);
bool StringHashTableIsKeyExists (struct StringHashTable * self_ptr, const char* key);
StringKeyAndValuePair  StringHashTableGet (struct StringHashTable * self_ptr, const char* key);
StringKeyAndValuePair  StringHashTableRemove (struct StringHashTable * self_ptr, const char* key);


static const StringBucket DEFAULT_STRING_BUCKET_TEMPLATE = {
	.m_key = NULL,
	.m_value = 0,
	.m_is_occupied = false
};

static const StringHashTable DEFAULT_STRING_HASHTABLE_TEMPLATE = {
	.m_array_ptr = NULL,
	.m_bucket_idx = 0,
	.hash = StringHashTableFunction,
	.add = StringHashTableAdd,
	.is_key_exists = StringHashTableIsKeyExists,
	.get = StringHashTableGet,
	.remove = StringHashTableRemove
};

#endif//__HEADER_GUARD_STRING_HASHTABLE__
