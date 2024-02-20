// Copyright 2022 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/student/struct.h"
#include "/home/student/ht.h"
#include "/home/student/ll.h"

/*
 * Key compare function.
 */
int compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;
	return strcmp(str_a, str_b);
}

/*
 * Hash functions.
 */
unsigned int
hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char *)a;
	__int32_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

/*
 * Function that allocates and initialises a hashtable.
 */
hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
		  int (*compare_function)(void *, void *))
{
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));
	hashtable->buckets = malloc(hmax * sizeof(linked_list_t *));
	for (unsigned int i = 0; i < hmax; i++)
		hashtable->buckets[i] = ll_create(sizeof(info));
	hashtable->hmax = hmax;
	hashtable->hash_function = hash_function;
	hashtable->compare_function = compare_function;
	hashtable->size = 0;
	return hashtable;
}

/*
 * A function that returns 1 if the given key has a prevously associated
 * value and 0 otherwise.
 */
int ht_has_key(hashtable_t *ht, void *key)
{
	int hash_id = ht->hash_function(key);
	int bucket_id = hash_id % ht->hmax;
	ll_node_t *current = ht->buckets[bucket_id]->head;
	while (current)
	{
		info *data = (info *)current->data;
		if (ht->compare_function(data->key, key) == 0)
			return 1;
		current = current->next;
	}
	return 0;
}

/*
 * A function that returns 1 the value associated with the given key.
 */
void *
ht_get(hashtable_t *ht, void *key)
{
	int hash_id = ht->hash_function(key);
	int bucket_id = hash_id % ht->hmax;
	ll_node_t *current = ht->buckets[bucket_id]->head;
	info *data = (info *)current->data;
	while (ht->compare_function(data->key, key) != 0)
	{
		if (current != NULL)
			current = current->next;
		data = (info *)current->data;
	}
	return data->value;
}

/*
 * A functions that adds a key-value pair the the hashtable;
 */
void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
			void *value, unsigned int value_size)
{
	int index = ht->hash_function(key) % ht->hmax;
	info *new_data = malloc(sizeof(info));
	if (ht_has_key(ht, key))
	{
		void *val = ht_get(ht, key);
		memcpy(val, value, value_size);
		return;
	}
	new_data->key = malloc(key_size);
	new_data->value = malloc(value_size);
	memcpy(new_data->key, key, key_size);
	memcpy(new_data->value, value, value_size);
	ll_add_nth_node(ht->buckets[index], 0, new_data);
	free(new_data);
	ht->size++;
}

/*
 * A function that frees all the memory used by the hashtable entries
 * and then also that of the hashtbale itself.
 */
void ht_free(hashtable_t *ht)
{
	for (unsigned int i = 0; i < ht->hmax; i++)
	{
		linked_list_t *list = ht->buckets[i];
		ll_node_t *current = list->head;
		while (current)
		{
			info *removed_data = (info *)current->data;
			free(removed_data->key);
			free(removed_data->value);
			current = current->next;
		}
		ll_free(&list);
	}
	free(ht->buckets);
	free(ht);
}

/*
 * A function that returns the size of the hashtable.
 */
unsigned int
ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}

/*
 * A function that returns the maximum size of the hashtable.
 */
unsigned int
ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}

/*
 * A function that removes a specific type of entry from a hashtable
 * more specifically, a hashtable.
 */
void ht_remove_book(hashtable_t *ht, void *key)
{
	int ok = 0, count = 0;
	int hash_id = ht->hash_function(key);
	int bucket_id = hash_id % ht->hmax;
	linked_list_t *list = ht->buckets[bucket_id];
	ll_node_t *removed = ht->buckets[bucket_id]->head;
	while (removed && !ok)
	{
		if (ht->compare_function(((info *)removed->data)->key, key) == 0)
			ok = 1;
		if (!ok)
		{
			removed = removed->next;
			count++;
		}
	}
	removed = ll_remove_nth_node(list, count);
	info *removed_data = (info *)removed->data;
	book_t *book_data = removed_data->value;
	ht_free(book_data->ht);
	free(removed_data->key);
	free(removed_data->value);
	free(removed->data);
	free(removed);
	ht->size--;
}

/*
 * A function that removes a specific type of entry from a hashtable
 * more specifically, a pair of value and key of any type.
 */
void ht_remove_def(hashtable_t *ht, void *key)
{
	int ok = 0, count = 0;
	int hash_id = ht->hash_function(key);
	int bucket_id = hash_id % ht->hmax;
	linked_list_t *list = ht->buckets[bucket_id];
	ll_node_t *removed = ht->buckets[bucket_id]->head;
	while (removed && !ok)
	{
		if (ht->compare_function(((info *)removed->data)->key, key) == 0)
			ok = 1;
		if (!ok)
		{
			removed = removed->next;
			count++;
		}
	}
	removed = ll_remove_nth_node(list, count);
	info *removed_data = (info *)removed->data;
	free(removed_data->key);
	free(removed_data->value);
	free(removed->data);
	free(removed);
	ht->size--;
}
